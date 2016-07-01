// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_MATRIXMATRIXADDITION_H_
#define SRC_BENCHMARK_MATRIXMATRIXADDITION_H_

#include "ActionBase.h"
#include "ActionSettingsBase.h"
#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#include "BlasBooster/Utilities/Settings.h"
#include <thread>

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixAddition, ActionSettingsBase, \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	void execute(BrainTwister::BenchmarkManager const& benchmark_manager) const; \
)

template <class Interface>
struct MatrixMatrixAdditionAction : public ActionBase
{
	~MatrixMatrixAdditionAction() {};

	std::string name() const { return "MatrixMatrixAddition"; }

	void initialize() const {}

	void execute() const {
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	void check() const {}
};

void MatrixMatrixAddition::execute(BrainTwister::BenchmarkManager const& bm) const
{
    // TODO
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXADDITION_H_ */
