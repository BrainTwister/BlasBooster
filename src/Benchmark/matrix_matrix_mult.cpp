#include "BlasBooster/Core/DenseMatrix.h"
#include "BrainTwister/benchmark.h"

std::tuple<BrainTwister::Benchmark::Results, Matrix<Dense,double>>
run_action(Matrix<Dense,double> const& refA, Matrix<Dense,double> const& refB, Benchmark const& benchmark)
{
	Matrix<Dense, float> A(refA);
	Matrix<Dense, float> B(refB);
	Matrix<Dense, float> C;

	auto result = benchmark.benchIt([&](){
		C = (A * B).template execute<OpenBLAS>();
	});

	return make_tuple(result, C);
}
