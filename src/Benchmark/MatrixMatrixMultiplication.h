// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_
#define SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_

#include "ActionBase.h"
#include "ActionSettingsBase.h"
#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#include "BlasBooster/Core/DynamicMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Utilities/Settings.h"
#include <thread>

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixMultiplication, ActionSettingsBase, \
	((std::vector<std::string>, matrix_types, std::vector<std::string>())) \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	virtual std::vector<Benchmark::PtrActionBase> get_actions() const; \
)

template <class Interface>
struct MatrixMatrixMultiplicationAction : public ActionBase
{
	MatrixMatrixMultiplicationAction(DynamicMatrix dynA, DynamicMatrix dynB)
	 : dynA(dynA), dynB(dynB)
	{}

	~MatrixMatrixMultiplicationAction()	{}

	std::string name() const { return "MatrixMatrixMultiplication"; }

	void initialize() const {}

	void execute() const {
		DynamicMatrix dynC = (dynA * dynB).template execute<Interface>();
	}

	void check() const {}

	DynamicMatrix dynA;
	DynamicMatrix dynB;
};

std::vector<Benchmark::PtrActionBase> MatrixMatrixMultiplication::get_actions() const
{
	std::vector<Benchmark::PtrActionBase> result;
	for (auto const& matrix_A : matrix_types)
	{
		for (auto const& size : sizes)
		{
			DynamicMatrix dynA;
			DynamicMatrix dynB;
			result.push_back(std::make_shared<MatrixMatrixMultiplicationAction<TheBestPolicy>>(dynA, dynB));
		}
	}
	return result;
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_ */
