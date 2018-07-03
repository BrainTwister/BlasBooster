#include "matrix_matrix_mult.h"

#include <stddef.h>
#include <chrono>
#include <iostream>
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

std::tuple<BrainTwister::Benchmark::Results, Matrix<Dense,double>>
matrix_matrix_mult(std::string const& action, BrainTwister::Benchmark const& benchmark, Threshold const& threshold,
    Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB)
{
#ifdef WITH_OPENBLAS
	if (action == "openblas_dgemm") {
		Matrix<Dense, double> C;
		auto result = benchmark.benchIt([&](){
			C = (refA * refB).template execute<OpenBLAS>();
		});
		return std::make_tuple(result, C);
	} else if (action == "openblas_sgemm") {
		Matrix<Dense, float> A(refA);
		Matrix<Dense, float> B(refB);
		Matrix<Dense, float> C;

		auto result = benchmark.benchIt([&](){
			C = (A * B).template execute<OpenBLAS>();
		});

		return std::make_tuple(result, Matrix<Dense, double>(C));

	} else
#endif
#ifdef WITH_INTELMKL
	if (action == "intelmkl_dgemm") {
		Matrix<Dense, double> C;
		auto result = benchmark.benchIt([&](){
			C = (refA * refB).template execute<IntelMKL>();
		});
		return std::make_tuple(result, C);
	} else if (action == "intelmkl_sgemm") {
		Matrix<Dense, float> A(refA);
		Matrix<Dense, float> B(refB);
		Matrix<Dense, float> C;

		auto result = benchmark.benchIt([&](){
			C = (A * B).template execute<IntelMKL>();
		});

		return std::make_tuple(result, Matrix<Dense, double>(C));

	} else
#endif
	if (action == "intelmkl_sgemm") {
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

		return std::make_tuple(result, Matrix<Dense, double>(C));

	} else {
		std::runtime_error("Unknown action: " + action);
	}
}

} // namespace BlasBooster
