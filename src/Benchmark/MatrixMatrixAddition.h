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
	virtual std::vector<Benchmark::PtrActionBase> get_actions() const; \
)

template <class Interface>
struct MatrixMatrixAdditionAction : public ActionBase
{
	~MatrixMatrixAdditionAction() {};

	std::string name() const { return "MatrixMatrixAddition"; }

	void initialize() const {}

	void execute() const {
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}

	void check() const {}
};

std::vector<Benchmark::PtrActionBase> MatrixMatrixAddition::get_actions() const
{
	std::vector<Benchmark::PtrActionBase> result;
	result.push_back(std::make_shared<MatrixMatrixAdditionAction<IntelMKL>>());
	return result;
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXADDITION_H_ */
