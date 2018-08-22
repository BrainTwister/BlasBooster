#pragma once

#include "ActionBase.h"
#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/Threshold.h"

namespace BlasBooster {

struct Action_blasbooster_block : public ActionBase
{
	BRAINTWISTER_RECORD( Settings, \
	    (( ThresholdSettings, threshold, ThresholdSettings{} )) \
	);

	Action_blasbooster_block(ptree const& tree)
     : settings(tree)
    {}

	std::string name() const { return "blasbooster_block"; }

    ActionBase::ReturnType execute(
    	Matrix<Dense,double> const& refA,
        Matrix<Dense,double> const& refB,
        BrainTwister::Benchmark const& benchmark) const
    {
    	const Threshold threshold{settings.threshold};
    	std::vector<size_t> bs_row_A, bs_col_A_row_B, bs_col_B;

		auto result1 = benchmark.benchIt([&](){
			std::tie(bs_row_A, bs_col_A_row_B, bs_col_B) =
				BlockSizeGenerator(threshold.get_min_block_size(), threshold.get_max_block_size()).matrix_matrix_mult(refA, refB);
		});
		Details details;
		details.push_back(std::make_tuple("size", result1.average_time));

		BlockedDenseMatrix A, B;

		auto result2 = benchmark.benchIt([&](){
			A = BlockedMatrixGenerator()(refA, bs_row_A, bs_col_A_row_B, threshold);
			B = BlockedMatrixGenerator()(refB, bs_col_A_row_B, bs_col_B, threshold);
		});
		details.push_back(std::make_tuple("block", result2.average_time));

		BlockedDenseMatrix C2;
		auto result3 = benchmark.benchIt([&](){
			C2 = (A * B).template execute<TheBestPolicy>();
		});
		details.push_back(std::make_tuple("mult", result3.average_time));

		Matrix<Dense,double> C = C2;
		return std::make_tuple(C, result1.average_time + result2.average_time + result3.average_time, details);
    }

    Settings settings;
};

} // namespace BlasBooster
