#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/benchmark.h"
#include <iostream>
#include <memory>

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        std::cout << "BlasBooster " + version + " Benchmark" << std::endl;

        Threshold threshold;
        //DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, DiagonalFiller<double>(1e-8)));
        DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(1e-8)));
        DynamicMatrix Z(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(0.0)));

        BrainTwister::benchmark benchmark;
//        BrainTwister::benchmark benchmark{JSON{R"(
//            {
//                "min_replications": 1,
//                "max_replications": 100000,
//                "min_execution_time": "00:00:00.100000000",
//                "spike_detection": 0,
//                "spike_detection_factor": 0.1,
//                "warm_up_runs": 0
//            }
//        )"}};

        BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
        const Matrix<Dense, double> refA{block};
        const Matrix<Dense, double> refB{block};
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
        {
            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> C;

            auto result = benchmark.benchIt([&](){
                C = A * B;
            });
            std::cout << "BlasBooster sparse "
            		  << std::chrono::duration_cast<std::chrono::milliseconds>(result.average_time).count() << " ms" << std::endl;

            Matrix<Dense, double> denseC(C);
            std::cout << "max-norm = " << std::scientific << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(denseC - refC) << std::endl;
        }
        {
        	std::pair<std::vector<size_t>, std::vector<size_t>> blockSizeA, blockSizeB;

            auto result = benchmark.benchIt([&](){
			    blockSizeA = BlockSizeGenerator(100, 200)(refA);
                blockSizeB = BlockSizeGenerator(100, 200)(refB);
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
            //std::cout << "max-norm = " << std::scientific << norm<NormMax>(denseC - refC) << std::endl;
            //std::cout << "  2-norm = " << std::scientific << norm<NormTwo>(denseC - refC) << std::endl;
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
