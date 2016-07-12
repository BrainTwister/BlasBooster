// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_
#define SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_

#include <boost/filesystem/path.hpp>
#include <stddef.h>
#include <string>
#include <vector>
#include "BrainTwister/BenchmarkManager.h"
#include "BlasBooster/Utilities/Settings.h"
#include "ActionSettingsBase.h"

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS(MatrixSet, \
    ((std::string, A, "")) \
    ((std::string, B, "")) \
    ((std::string, C, "")) \
)

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixMultiplication, ActionSettingsBase, \
	((std::vector<MatrixSet>, matrix_types, std::vector<MatrixSet>())) \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	void execute(BrainTwister::BenchmarkManager const& benchmark_manager) const; \
)

template <class MatrixTypeA, class MatrixTypeB, class MatrixTypeC, class Interface>
struct MatrixMatrixMultiplicationExecutor
{
	void operator () (MatrixMatrixMultiplication const& settings, BrainTwister::BenchmarkManager const& bm) const
	{
//		MatrixMatrixMultiplicationAction action;
//
//		BrainTwister::BenchmarkManager::Result result = bm.benchIt(action);
//		std::cout << action.name() << " "
//				  << result.nbReplications << " "
//				  << result.num_spikes << " "
//				  << std::chrono::duration_cast<std::chrono::microseconds>(result.averageTime).count() << " microsec" << std::endl;
	}
};

void MatrixMatrixMultiplication::execute(BrainTwister::BenchmarkManager const& bm) const
{
	for (auto const& matrix_set : matrix_types)
	{
		for (auto const& interface : interfaces)
		{
//			exec_dyn_4dim<
//			    DynamicMatrixTypeList,
//			    DynamicMatrixTypeList,
//			    DynamicMatrixTypeList,
//			    InterfaceTypeList,
//				MatrixMatrixMultiplicationExecutor
//			>(matrix_set.A, matrix_set.B, matrix_set.C, interface)(*this, bm);
		}
	}
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_ */
