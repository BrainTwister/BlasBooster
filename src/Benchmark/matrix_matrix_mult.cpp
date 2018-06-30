#include "BlasBooster/Core/DenseMatrix.h"
#include "BrainTwister/benchmark.h"

std::tuple<BrainTwister::Benchmark::Results, double, double>
matrix_matrix_mult(Matrix<Dense,double> const& refA,
    Matrix<Dense,double> const& refB, Matrix<Dense,double> const& refC, Benchmark const& benchmark)
{
	Matrix<Dense, float> A(refA);
	Matrix<Dense, float> B(refB);
	Matrix<Dense, float> C;

	auto result = benchmark.benchIt([&](){
		C = (A * B).template execute<OpenBLAS>();
	});

	auto diff = C - refC;
	return make_tuple(result, norm<NormMax>(diff), norm<NormTwo>(diff));
}
