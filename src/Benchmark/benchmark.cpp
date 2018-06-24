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

using namespace BlasBooster;

BRAINTWISTER_RECORD(Settings, \
    ((ThresholdSettings, threshold, ThresholdSettings{})) \
    ((BrainTwister::Benchmark::Settings, benchmark, BrainTwister::Benchmark::Settings{})) \
    ((int, OpenBLAS_num_threads, 1)) \
    ((int, IntelMKL_num_threads, 1)) \
);

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Benchmark\n" << std::endl;

        std::string matrix_file, settings_file;
        bool show_help = true;
        auto cli = clara::Help(show_help)
        		 | clara::Opt(matrix_file, "matrix")
                      ["-m"]["--matrix"]
                      ("Matrix filename")
	             | clara::Opt(settings_file, "settings")
                      ["-s"]["--settings"]
                      ("Settings filename");

        auto r = cli.parse(clara::Args(argc, argv));
        if(!r) {
            std::cerr << "Error in command line: " << r.errorMessage() << std::endl;
            return 1;
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

        const Matrix<Dense, double> refA(matrix_file);
        const Matrix<Dense, double> refB(matrix_file);
        Matrix<Dense, double> refC;

        auto result = benchmark.benchIt([&](){
        	refC = (refA * refB).template execute<OpenBLAS>();
        });
        std::cout << "OpenBLAS dgemm "
        		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

        {
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C;

            auto result = benchmark.benchIt([&](){
                C = (A * B).template execute<OpenBLAS>();
            });
            std::cout << "OpenBLAS sgemm "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

            std::cout << "max-norm = " << std::scientific << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(C - refC) << std::endl;
        }
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
#endif
//        {
//            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
//            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
//            Matrix<Sparse, double> C;
//
//            auto result = benchmark.benchIt([&](){
//                C = A * B;
//            });
//            std::cout << "BlasBooster sparse "
//            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;
//
//            Matrix<Dense, double> denseC(C);
//            std::cout << "max-norm = " << std::scientific << norm<NormMax>(denseC - refC) << std::endl;
//            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(denseC - refC) << std::endl;
//        }
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

            std::cout << generateTypeMatrix(A) << std::endl;
            std::cout << generateDimensionMatrix(A) << std::endl;
            //std::cout << generateNormMatrix(A) << std::endl;

            BlockedDenseMatrix C;
            auto result3 = benchmark.benchIt([&](){
            	C = (A * B).template execute<TheBestPolicy>();
            });
            std::cout << "BlasBooster block mult "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result3.average_time).count() << " ms" << std::endl;

            std::cout << generateTypeMatrix(C) << std::endl;

            Matrix<Dense, double> denseC(C);
            std::cout << "max-norm = " << std::scientific << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(denseC - refC) << std::endl;
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
