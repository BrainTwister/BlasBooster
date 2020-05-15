#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

#include "ActionProvider.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/range.h"
#include "BlasBooster/Utilities/Tracker.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/benchmark.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "clara.hpp"
#include "MatrixProvider.h"
#include "time.h"
#include <range/v3/view/indices.hpp>
#include <range/v3/view/zip.hpp>

using namespace BlasBooster;

BRAINTWISTER_RECORD( Settings, \
    (( ActionProvider, actions, ActionProvider{} )) \
    (( MatrixProvider, matrices, MatrixProvider{} )) \
    (( BrainTwister::Benchmark::Settings, benchmark, BrainTwister::Benchmark::Settings{} )) \
);

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Benchmark\n" << std::endl;

        std::string settings_file = "benchmark.json";
        std::string diff_file = "diff.dat";
        bool write_diff = false;
        int duration_digits = 3;
        bool show_help = false;
        auto cli = clara::Help(show_help)
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (default: benchmark.json)")
                 | clara::Opt(duration_digits, "duration_digits")["-a"]["--duration_digits"]("Number of digits of time duration (default: 3)")
                 | clara::Opt(write_diff)["-d"]["--diff"]("Write difference matrix (default: off)");

        auto cli_result = cli.parse(clara::Args(argc, argv));
        if (!cli_result)
        {
            std::cerr << cli << std::endl;
            std::cerr << "Error in command line: " << cli_result.errorMessage() << std::endl;
            return 1;
        }

        if (show_help)
        {
            std::cerr << cli << std::endl;
            return 0;
        }

        std::ifstream ifs{settings_file};
        std::string settings_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        const Settings settings{JSON{settings_str}};
        const BrainTwister::Benchmark benchmark{settings.benchmark};

        std::cout << std::scientific
                  << set_duration_accuracy(duration_digits) << "\n"
                  << std::setw(10) << std::left << "matrix"
                  << std::setw(30) << std::left << "name"
                  << std::setw(15) << "time/s"
                  << std::setw(15) << "max-norm"
                  << std::setw(15) << "2-norm"
                  << "details\n"
                  << std::string(120,'-')
                  << std::endl;

        auto&& actions = settings.actions.get();
        auto&& list_A = settings.matrices.get("A");
        auto&& list_B = settings.matrices.get("B");
        if (list_A.size() == 0) throw std::runtime_error("No matrices defined");
        if (list_A.size() != list_B.size()) throw std::runtime_error("Number of matrices A and B not equal");
        if (actions.size() == 0) throw std::runtime_error("No actions defined");

        for (auto&& [A, B, i] : ranges::views::zip(list_A, list_B, ranges::views::indices(list_A.size())))
        {
            std::cout << std::setw(10) << std::left << i
                      << std::setw(30) << std::left << actions[0]->name() << std::flush;

            auto&& [refC, time, details] = actions[0]->execute(A, B, benchmark);

            std::cout << std::setw(15) << time
                      << std::setw(15) << 0.0
                      << std::setw(15) << 0.0
                      << details
                      << std::endl;

            for (auto&& action : range(actions.begin()+1, actions.end()))
            {
                std::cout << std::setw(10) << std::left << i
                          << std::setw(30) << std::left << action->name() << std::flush;

                auto&& [C, time, details] = action->execute(A, B, benchmark);
                auto&& diff = C - refC;

                std::cout << set_duration_accuracy(duration_digits)
                          << std::setw(15) << time
                          << std::setw(15) << norm<NormMax>(diff)
                          << std::setw(15) << norm<NormTwo>(diff)
                          << details
                          << std::endl;

                if (write_diff) {
                    std::ofstream os(std::string("diff_") + std::to_string(i) + ".dat", std::ofstream::binary);
                    os.write(reinterpret_cast<const char*>(diff.getDataPointer()), diff.getSize()*sizeof(double));
                }
            }
        }

#ifdef BLASBOOSTER_USE_TRACKER
        TrackerRegister::print(std::cout << set_duration_accuracy(duration_digits));
#endif

    } catch ( BlasBoosterException const& e ) {
        std::cout << "BlasBooster exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    } catch ( std::exception const& e ) {
        std::cout << "Standard exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    } catch ( ... ) {
        std::cout << "Unknown exception." << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    }

    std::cout << "\n BlasBooster successfully finished. Have a nice day.\n" << std::endl;

}
