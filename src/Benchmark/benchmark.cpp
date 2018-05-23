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
#include <iostream>
#include <memory>

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        std::cout << "BlasBooster " + version + " Benchmark" << std::endl;

        Threshold threshold;
//        Threshold threshold(ThresholdSettings(JSON{R"(
//            {
//                "significanceThresholdSinglePrecision":                                    1e-5,
//                "significanceThresholdDoublePrecision":                                    1e-10,
//                "occupationThresholdMatrixSparseFloatSinglePrecision":                     0.0,
//                "occupationThresholdMatrixSparseFloatDoublePrecision":                     0.1,
//                "occupationThresholdMatrixDenseFloatSinglePrecision":                      0.0,
//                "occupationThresholdMatrixDenseFloatDoublePrecision":                      1.0,
//                "occupationThresholdMatrixSparseDoubleSinglePrecision":                    0.1,
//                "occupationThresholdMatrixSparseDoubleDoublePrecision":                    0.1,
//                "occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision": 0.1,
//                "occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision": 0.2,
//                "occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision":  0.1,
//                "occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision":  1.0,
//                "occupationThresholdMatrixDenseDoubleSinglePrecision":                     1.0,
//                "occupationThresholdMatrixDenseDoubleDoublePrecision":                     1.0
//            }
//        )"}));

        DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(1e-8)));
        DynamicMatrix Z(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(0.0)));

        BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
        const Matrix<Dense, double> refA{block};
        const Matrix<Dense, double> refB{block};
        Matrix<Dense, double> refC;

        {
            ScopedTimer scopedTimer("OpenBLAS dgemm");
            refC = (refA * refB).template execute<OpenBLAS>();
        }
        {
            ScopedTimer scopedTimer("OpenBLAS sgemm");
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C = (A * B).template execute<OpenBLAS>();

            std::cout << "max-norm = " << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(C - refC) << std::endl;
        }
        {
            ScopedTimer scopedTimer("OpenBLAS sgemm 1000x1000");
            Matrix<Dense, float> A(1000, 1000, AllFiller<double>(1.0));
            Matrix<Dense, float> B(1000, 1000, AllFiller<double>(1.0));
            auto C = (A * B).template execute<OpenBLAS>();
        }
        {
            ScopedTimer scopedTimer("sparse double");
            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> C = A * B;

            Matrix<Dense, double> denseC(C);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
        }
        {
            ScopedTimer scopedTimer("blocked multiplication");

            std::unique_ptr<ScopedTimer> ptrScopedTimer(new ScopedTimer("blocked multiplication, block size"));
            auto blockSizeA = BlockSizeGenerator(500, 1000)(refA);
            auto blockSizeB = BlockSizeGenerator(500, 1000)(refB);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, blocking"));
            BlockedDenseMatrix A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, threshold);
            BlockedDenseMatrix B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, threshold);

            std::cout << generateTypeMatrix(A) << std::endl;
            std::cout << generateDimensionMatrix(A) << std::endl;
            //std::cout << generateNormMatrix(A) << std::endl;

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, mult"));
            BlockedDenseMatrix C = (A * B).template execute<TheBestPolicy>();

            Matrix<Dense, double> denseC(C);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
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
