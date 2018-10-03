#pragma once

#include "ActionBase.h"
#include "BlasBooster/Core/Multiplication_Native.h"

namespace BlasBooster {

struct Action_native_dense : public ActionBase
{
	BRAINTWISTER_RECORD( Settings, \
	    (( int, number_of_threads, 1 )) \
	);

	Action_native_dense(ptree const& tree)
     : settings(tree)
    {}

	std::string name() const { return "native_dense"; }

    ActionBase::ReturnType execute(
    	Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const
    {
		Matrix<Dense, double> C;
		auto result = benchmark.benchIt([&](){
			GeneralDenseMultiplicationFunctor<double, Parameter<>, double, Parameter<>, double, Parameter<>>()(refA, refB, C);
		});

		Details details;
		return std::make_tuple(C, result.average_time, details);
    }

    Settings settings;
};

} // namespace BlasBooster
