#include <chrono>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
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

#ifdef WITH_OPENBLAS
  #include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"
#endif
#ifdef WITH_INTELMKL
  #include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#endif

using namespace BlasBooster;

BRAINTWISTER_RECORD(Settings, \
    ((ThresholdSettings, threshold, ThresholdSettings{})) \
    ((BrainTwister::Benchmark::Settings, benchmark, BrainTwister::Benchmark::Settings{})) \
    ((int, OpenBLAS_num_threads, 1)) \
    ((int, IntelMKL_num_threads, 1)) \
    ((std::vector<std::string>, actions, std::vector<std::string>())) \
);

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Benchmark\n" << std::endl;

        std::string matrix_file_A, matrix_file_B, settings_file;
        std::string diff_file = "diff.dat";
        bool write_diff = false;
        bool show_help = false;
        auto cli = clara::Help(show_help)
                 | clara::Arg(matrix_file_A, "matrix A")("Input file of matrix A (*.xml)").required()
                 | clara::Arg(matrix_file_B, "matrix B")("Input file of matrix B (*.xml)").required()
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (*.json)")
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
                  << std::setw(30) << std::left << "name"
                  << std::setw(15) << "time/ms"
                  << std::setw(15) << "max-norm"
                  << std::setw(15) << "2-norm"
				  << "details\n"
                  << std::string(120,'-')
                  << std::endl;

        const Matrix<Dense, double> A(matrix_file_A);
        const Matrix<Dense, double> B(matrix_file_B);

        std::cout << std::setw(30) << std::left << settings.actions[0] << std::flush;

        // C++17
        //auto const& [refC, time, details] = matrix_matrix_mult(settings.actions[0], benchmark, threshold, A, B);
        auto const& rv1 = matrix_matrix_mult(settings.actions[0], benchmark, threshold, A, B);
        auto const& refC = std::get<0>(rv1);
        auto const& time = std::get<1>(rv1);
        auto const& details = std::get<2>(rv1);

        std::cout << std::setw(15) << time
                  << std::setw(15) << 0.0
                  << std::setw(15) << 0.0
                  << std::setw(50) << details
                  << std::endl;

        for (auto&& action : range(settings.actions.begin()+1, settings.actions.end()))
        {
            std::cout << std::setw(30) << action << std::flush;

            // C++17
            //auto const& [C, time, details] = matrix_matrix_mult(settings.actions[0], benchmark, threshold, A, B);
            auto const& rv2 = matrix_matrix_mult(action, benchmark, threshold, A, B);
            auto const& C = std::get<0>(rv2);
            auto const& time = std::get<1>(rv2);
            auto const& details = std::get<2>(rv2);
            auto const diff = C - refC;

            if (write_diff) {
                std::ofstream os(diff_file, std::ofstream::binary);
                os.write(reinterpret_cast<const char*>(diff.getDataPointer()), diff.getSize()*sizeof(double));
            }
            std::cout << std::setw(15) << time
                      << std::setw(15) << norm<NormMax>(diff)
                      << std::setw(15) << norm<NormTwo>(diff)
                      << std::setw(50) << details
                      << std::endl;
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
