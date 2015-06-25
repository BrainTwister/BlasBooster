#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
//#include "BrainTwister/ArgumentParser.h"
#include <iostream>
#include <memory>
//#include "omp.h"

using namespace BlasBooster;
//namespace bt = BrainTwister;

int main(int argc, char* argv[])
{
    try {

        std::cout << "BlasBooster " + version + " Benchmark" << std::endl;

//        std::cout << "TestSuite set number of threads = 1" << std::endl;
//        omp_set_num_threads(1);

        Threshold threshold(ThresholdSettings(
            1e-5,  // std::numeric_limits<float>::epsilon()
            1e-10, // std::numeric_limits<double>::epsilon()
            0.0,   // 0.0    occupationThresholdMatrixSparseFloatSinglePrecision
            0.1,   // 0.2    occupationThresholdMatrixSparseFloatDoublePrecision
            0.0,   // 0.0    occupationThresholdMatrixDenseFloatSinglePrecision
            1.0,   // 1.0    occupationThresholdMatrixDenseFloatDoublePrecision
            0.1,   // 0.2    occupationThresholdMatrixSparseDoubleSinglePrecision
            0.1,   // 0.2    occupationThresholdMatrixSparseDoubleDoublePrecision
            0.1,   // 0.2    occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision
            0.2,   // 0.4    occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision
            0.1,   // 0.2    occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision
            1.0,   // 1.0    occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision
            1.0,   // 1.0    occupationThresholdMatrixDenseDoubleSinglePrecision
            1.0    // 1.0    occupationThresholdMatrixDenseDoubleDoublePrecision
        ));

#if 0
        bt::ArgumentParser arg(argc, argv, bt::Equal(2),
            {{"input", 'i', bt::Value<std::string>(), "Description of option input."},
             {"verbose", bt::Value<bool>(), "Print more output."}}
        );
#endif

        const Matrix<Dense, double> refA(1000, 1000, NoFiller());
        const Matrix<Dense, double> refB(1000, 1000, NoFiller());
        Matrix<Dense, double> refC;

        {
            ScopedTimer scopedTimer("Intel MKL dgemm");
            refC = (refA * refB).template execute<IntelMKL>();
        }
        {
            ScopedTimer scopedTimer("Intel MKL sgemm");
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C = (A * B).template execute<IntelMKL>();

            std::cout << "max-norm = " << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(C - refC) << std::endl;
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
            auto blockSizeA = BlockSizeGenerator(50, 200)(refA);
            auto blockSizeB = BlockSizeGenerator(50, 200)(refB);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, blocking"));
            BlockedDenseMatrix A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, threshold);
            BlockedDenseMatrix B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, threshold);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, mult"));
            BlockedDenseMatrix C = (A * B).template execute<Native>();

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

