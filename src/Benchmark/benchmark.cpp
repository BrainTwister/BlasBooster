#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "BlasBooster/Core/Norm.h"
#include "BlasBooster/Core/Parameter.h"
#include "BlasBooster/Core/Threshold.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/range.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/benchmark.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "clara.hpp"
#include "matrix_matrix_mult.h"
#include "MatrixProvider.h"
#include <range/v3/view/indices.hpp>
#include <range/v3/view/zip.hpp>

#ifdef WITH_OPENBLAS
  #include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"
#endif
#ifdef WITH_INTELMKL
  #include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#endif

using namespace BlasBooster;
using namespace ranges;

BRAINTWISTER_RECORD( Settings, \
    (( std::vector<std::string>, actions, std::vector<std::string>() )) \
    (( MatrixProvider, matrices, MatrixProvider() )) \
    (( int, IntelMKL_num_threads, 1 )) \
    (( int, OpenBLAS_num_threads, 1 )) \
    (( ThresholdSettings, threshold, ThresholdSettings{} )) \
    (( BrainTwister::Benchmark::Settings, benchmark, BrainTwister::Benchmark::Settings{} )) \
);

size_t scale_time(size_t time, std::string time_prefix) {
    if (time_prefix == "micro") return time /= 1000;
    if (time_prefix == "milli") return time /= 1000000;
    return time;
}

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Benchmark\n" << std::endl;

        std::string settings_file = "benchmark.json";
        std::string diff_file = "diff.dat";
        bool write_diff = false;
        std::string time_prefix = "nano";
        bool show_help = false;
        auto cli = clara::Help(show_help)
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (*.json)")
                 | clara::Opt(time_prefix, "time_prefix")["-t"]["--time-prefix"]("Prefix for time listing (default: nano)")
                 | clara::Opt(write_diff)["-d"]["--diff"]("Write difference matrix (default: off)")
                 | clara::Opt(diff_file, "diff matrix")["--diff-matrix"]("Output file for difference matrix between reference and block mult (diff.dat)");

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

        std::string time_prefix_symbol = "n";
        if (time_prefix == "nano") time_prefix_symbol = "n";
        else if (time_prefix == "micro") time_prefix_symbol = "u";
        else if (time_prefix == "milli") time_prefix_symbol = "m";
        else std::runtime_error(std::string("Unknown option for time_prefix: ") + time_prefix);

        std::ifstream ifs{settings_file};
        std::string settings_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        const Settings settings{JSON{settings_str}};
        const Threshold threshold{settings.threshold};
        const BrainTwister::Benchmark benchmark{settings.benchmark};

#ifdef WITH_OPENBLAS
        std::cout << "Set number of threads for OpenBLAS to " << settings.OpenBLAS_num_threads << std::endl;
        OpenBLAS_set_num_threads(settings.OpenBLAS_num_threads);
#endif
#ifdef WITH_INTELMKL
        std::cout << "Set number of threads for IntelMKL to " << settings.IntelMKL_num_threads << std::endl;
        IntelMKL_set_num_threads(settings.IntelMKL_num_threads);
#endif

        std::cout << std::scientific << "\n"
                  << std::setw(10) << std::left << "matrix"
                  << std::setw(30) << std::left << "name"
                  << std::setw(15) << std::string("time/") + time_prefix_symbol + "s"
                  << std::setw(15) << "max-norm"
                  << std::setw(15) << "2-norm"
                  << "details\n"
                  << std::string(120,'-')
                  << std::endl;

        auto&& list_A = settings.matrices.get("A");
        auto&& list_B = settings.matrices.get("B");
        if (list_A.size() != list_B.size()) std::runtime_error("Number of matrices A and B not equal");

        for (auto&& [A, B, i] : view::zip(list_A, list_B, view::indices(list_A.size())))
        {
            std::cout << std::setw(10) << std::left << i
            		  << std::setw(30) << std::left << settings.actions[0] << std::flush;

            auto&& [refC, time, details] = matrix_matrix_mult(settings.actions[0], benchmark, threshold, A, B);

            std::cout << std::setw(15) << scale_time(time, time_prefix)
                      << std::setw(15) << 0.0
                      << std::setw(15) << 0.0
                      << std::setw(50) << details
                      << std::endl;

            for (auto&& action : range(settings.actions.begin()+1, settings.actions.end()))
            {
                std::cout << std::setw(10) << std::left << i
                		  << std::setw(30) << std::left << action << std::flush;

                auto&& [C, time, details] = matrix_matrix_mult(action, benchmark, threshold, A, B);
                auto&& diff = C - refC;

                std::cout << std::setw(15) << scale_time(time, time_prefix)
                          << std::setw(15) << norm<NormMax>(diff)
                          << std::setw(15) << norm<NormTwo>(diff)
                          << std::setw(50) << details
                          << std::endl;

                if (write_diff) {
                    std::ofstream os(diff_file, std::ofstream::binary);
                    os.write(reinterpret_cast<const char*>(diff.getDataPointer()), diff.getSize()*sizeof(double));
                }
            }
        }
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
