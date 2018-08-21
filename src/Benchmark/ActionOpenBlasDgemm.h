#pragma once

#include "ActionBase.h"
#include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"
#include "BlasBooster/Core/MatrixMultExp.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"

namespace BlasBooster {

struct ActionOpenBlasDgemm : public ActionBase
{
	BRAINTWISTER_RECORD( Settings, \
	    (( int, number_of_threads, 1 )) \
	);

    ActionOpenBlasDgemm(ptree const& tree)
     : settings(tree)
    {}

	std::string name() const { return "openblas_dgemm"; }

    ActionBase::ReturnType execution(
    	Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const
    {
		Matrix<Dense, double> C;
		Details details;

        OpenBLAS_set_num_threads(settings.number_of_threads);

		auto result = benchmark.benchIt([&](){
			C = (refA * refB).template execute<OpenBLAS>();
		});
		return std::make_tuple(C, result.average_time, details);
    }

    Settings settings;
};

} // namespace BlasBooster
