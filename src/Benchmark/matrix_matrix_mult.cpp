#include "matrix_matrix_mult.h"

#include <chrono>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixMultExp.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/Norm.h"
#include "BlasBooster/Core/Parameter.h"

namespace BlasBooster {

std::tuple<Matrix<Dense,double>, size_t, std::string>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark, Threshold const& threshold,
    Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB)
{
    Matrix<Dense, double> C;
    size_t time = 0;
    std::ostringstream details;

#ifdef WITH_OPENBLAS
    if (action == "openblas_dgemm")
    {
        auto result = benchmark.benchIt([&](){
            C = (refA * refB).template execute<OpenBLAS>();
        });
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "openblas_sgemm")
    {
        Matrix<Dense, float> A(refA);
        Matrix<Dense, float> B(refB);
        Matrix<Dense, float> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<OpenBLAS>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    } else
#endif
#ifdef WITH_INTELMKL
    if (action == "intelmkl_dgemm")
    {
        auto result = benchmark.benchIt([&](){
            C = (refA * refB).template execute<IntelMKL>();
        });
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "intelmkl_sgemm")
    {
        Matrix<Dense, float> A(refA);
        Matrix<Dense, float> B(refB);
        Matrix<Dense, float> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<IntelMKL>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "intelmkl_dcsrmm")
    {
        Matrix<Sparse, double> A(refA);
        Matrix<Dense, double> B(refB);

        auto result = benchmark.benchIt([&](){
            C = (A * B).template execute<IntelMKL>();
        });

        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "intelmkl_scsrmm")
    {
        Matrix<Sparse, float> A(refA);
        Matrix<Dense, float> B(refB);
        Matrix<Dense, float> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<IntelMKL>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "intelmkl_dcsrmultcsr")
    {
        Matrix<Sparse, double> A(refA);
        Matrix<Sparse, double> B(refB);
        Matrix<Sparse, double> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<IntelMKL>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "intelmkl_scsrmultcsr")
    {
        Matrix<Sparse, float> A(refA);
        Matrix<Sparse, float> B(refB);
        Matrix<Sparse, float> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<IntelMKL>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else
#endif
    if (action == "blasbooster_block")
    {
        std::pair<std::vector<size_t>, std::vector<size_t>> blockSizeA, blockSizeB;

        auto result1 = benchmark.benchIt([&](){
            blockSizeA = BlockSizeGenerator(200, 1000)(refA);
            blockSizeB = BlockSizeGenerator(200, 1000)(refB);
        });
        details << "size: "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(result1.average_time).count();

        BlockedDenseMatrix A, B;

        auto result2 = benchmark.benchIt([&](){
            A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, threshold);
            B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, threshold);
        });
        details << ", block "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(result2.average_time).count();

        BlockedDenseMatrix C2;
        auto result3 = benchmark.benchIt([&](){
            C2 = (A * B).template execute<TheBestPolicy>();
        });
        details << ", mult "
                << std::chrono::duration_cast<std::chrono::nanoseconds>(result3.average_time).count();

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result1.average_time).count()
             + std::chrono::duration_cast<std::chrono::nanoseconds>(result2.average_time).count()
             + std::chrono::duration_cast<std::chrono::nanoseconds>(result3.average_time).count();

    }
    else if (action == "blasbooster_sparse_double")
    {
        Matrix<Sparse, double> A(refA);
        Matrix<Sparse, double> B(refB);
        Matrix<Sparse, double> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<Native>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else if (action == "blasbooster_sparse_float")
    {
        Matrix<Sparse, float> A(refA);
        Matrix<Sparse, float> B(refB);
        Matrix<Sparse, float> C2;

        auto result = benchmark.benchIt([&](){
            C2 = (A * B).template execute<Native>();
        });

        C = C2;
        time = std::chrono::duration_cast<std::chrono::nanoseconds>(result.average_time).count();
    }
    else
    {
        std::runtime_error(std::string("Unknown action: ") + action);
    }

    return std::make_tuple(C, time, details.str());
}

} // namespace BlasBooster
