#pragma once

#include "ActionBase.h"
#include "BlasBooster/Core/MatrixMultExp.h"
#include "BlasBooster/Core/Multiplication_Blaze.h"

namespace BlasBooster {

struct Action_blaze_sgemm : public ActionBase
{
	BRAINTWISTER_RECORD( Settings, \
	    (( int, number_of_threads, 1 )) \
	);

	Action_blaze_sgemm(ptree const& tree)
     : settings(tree)
    {}

	std::string name() const { return "blaze_sgemm"; }

    ActionBase::ReturnType execute(
    	Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const
    {
        Matrix<Dense, float> A(refA);
        Matrix<Dense, float> B(refB);
        Matrix<Dense, float> C;

        auto result = benchmark.benchIt([&](){
            C = (A * B).template execute<Blaze>();
        });

		Details details;
		return std::make_tuple(Matrix<Dense, double>(C), result.average_time, details);
    }

    Settings settings;
};

} // namespace BlasBooster
