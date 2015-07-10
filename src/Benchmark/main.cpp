#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace BlasBooster;
namespace bt = BrainTwister;

int main(int argc, char* argv[])
{
    try {

        bt::ArgumentParser arg(argc, argv, version,
            {{"MatrixA", bt::Value<std::string>(), "File for matrix A."},
             {"MatrixB", bt::Value<std::string>(), "File for matrix B."}},
            {{"threads", "t", bt::Value<int>(1), "Number of threads."}}
        );

        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        int nbThreads = arg.get<int>("threads");
        std::cout << "Number of threads: " << nbThreads << std::endl;

        BlasBooster::mkl_set_num_threads(nbThreads);
        BlasBooster::openblas_set_num_threads(nbThreads);

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

        DynamicMatrix F(new Matrix<Dense,double>(1000,1000,HilbertFiller()));
        DynamicMatrix Z(new Matrix<Dense,double>(1000,1000,ZeroFiller()));

        BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
        const Matrix<Dense, double> refA{block};
        const Matrix<Dense, double> refB{block};
        Matrix<Dense, double> refC;

        {
            ScopedTimer scopedTimer("Intel MKL dgemm");
            refC = (refA * refB).template execute<IntelMKL>();
        }
        {
            ScopedTimer scopedTimer("OpenBLAS dgemm");
            Matrix<Dense, double> C = (refA * refB).template execute<OpenBLAS>();
        }
        {
            ScopedTimer scopedTimer("Intel MKL sgemm");
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C = (A * B).template execute<IntelMKL>();

            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(C - refC) << std::endl;
        }
        {
            ScopedTimer scopedTimer("sparse double");
            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> C = A * B;

            Matrix<Dense, double> denseC(C);
            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
        }
        {
            ScopedTimer scopedTimer("blocked multiplication");

            std::unique_ptr<ScopedTimer> ptrScopedTimer(new ScopedTimer("blocked multiplication, block size"));
            auto blockSizeA = BlockSizeGenerator(50, 2000)(refA);
            auto blockSizeB = BlockSizeGenerator(50, 2000)(refB);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, blocking"));
            BlockedDenseMatrix A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, threshold);
            BlockedDenseMatrix B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, threshold);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, mult"));
            BlockedDenseMatrix C = (A * B).template execute<TheBestPolicy>();

            Matrix<Dense, double> denseC(C);
            std::cout << std::scientific << std::setprecision(6);
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

