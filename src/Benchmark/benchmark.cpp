#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/benchmark.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "clara.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace BlasBooster;

BRAINTWISTER_RECORD(Settings, \
    ((ThresholdSettings, threshold, ThresholdSettings{})) \
    ((BrainTwister::Benchmark::Settings, benchmark, BrainTwister::Benchmark::Settings{})) \
    ((int, OpenBLAS_num_threads, 1)) \
    ((int, IntelMKL_num_threads, 1)) \
    ((std::vector<std::string>, actions, std::vector<std::string>{})) \
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

        if (auto error = cli.parse(clara::Args(argc, argv)))
        {
    	    std::cerr << cli << std::endl;
            std::cerr << "Error in command line: " << error.errorMessage() << std::endl;
            return 1;
        }

        if (show_help)
        {
    	    std::cerr << cli << std::endl;
            return 0;
        }

        std::ifstream ifs{settings_file};
        std::string settings_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        Settings settings{JSON{settings_str}};
        Threshold threshold{settings.threshold};
        BrainTwister::Benchmark benchmark{settings.benchmark};

#ifdef WITH_OPENBLAS
        std::cout << "Set number of threads for OpenBLAS to " << settings.OpenBLAS_num_threads << std::endl;
        OpenBLAS_set_num_threads(settings.OpenBLAS_num_threads);
#endif
#ifdef WITH_INTELMKL
        std::cout << "Set number of threads for IntelMKL to " << settings.IntelMKL_num_threads << std::endl;
        IntelMKL_set_num_threads(settings.IntelMKL_num_threads);
#endif

        const Matrix<Dense, double> refA(matrix_file_A);
        const Matrix<Dense, double> refB(matrix_file_B);

        auto const& [result, refC] = run_action(settings.actions[0], refA, refB);

        for (auto const& action : settings.actions) {

        }

        auto result = benchmark.benchIt([&](){
        	refC = (refA * refB).template execute<OpenBLAS>();
        });

        std::cout << "OpenBLAS dgemm "
        		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;


#ifdef WITH_INTELMKL
        {
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C;

            auto result = benchmark.benchIt([&](){
                C = (A * B).template execute<IntelMKL>();
            });
            std::cout << "IntelMKL sgemm "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

            std::cout << "max-norm = " << std::scientific << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(C - refC) << std::endl;
        }
        {
            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> C;

            auto result = benchmark.benchIt([&](){
                C = (A * B).template execute<IntelMKL>();
            });
            std::cout << "IntelMKL dcsrmultcsr "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

            Matrix<Dense, double> denseC(C);
            std::cout << "max-norm = " << std::scientific << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(denseC - refC) << std::endl;
        }
#endif
        {
        	std::pair<std::vector<size_t>, std::vector<size_t>> blockSizeA, blockSizeB;

            auto result = benchmark.benchIt([&](){
			    blockSizeA = BlockSizeGenerator(200, 1000)(refA);
                blockSizeB = BlockSizeGenerator(200, 1000)(refB);
            });
            std::cout << "BlasBooster block size "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

            BlockedDenseMatrix A, B;

            auto result2 = benchmark.benchIt([&](){
                A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, threshold);
                B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, threshold);
            });
            std::cout << "BlasBooster blocking "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result2.average_time).count() << " ms" << std::endl;

            BlockedDenseMatrix C;
            auto result3 = benchmark.benchIt([&](){
            	C = (A * B).template execute<TheBestPolicy>();
            });
            std::cout << "BlasBooster block mult "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result3.average_time).count() << " ms" << std::endl;

            Matrix<Dense, double> denseC(C);
            auto diffC = denseC - refC;
            std::cout << "max-norm = " << std::scientific << norm<NormMax>(diffC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(diffC) << std::endl;

            if (write_diff) {
                std::ofstream os(diff_file, std::ofstream::binary);
                os.write(reinterpret_cast<const char*>(diffC.getDataPointer()), diffC.getSize()*sizeof(double));
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
