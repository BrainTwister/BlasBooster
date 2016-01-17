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
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Utilities/Settings.h"
#include <thread>

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS(MatrixSet, \
    ((std::string, A, "test")) \
    ((std::string, B, "")) \
    ((std::string, C, "")) \
)

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixMultiplication, ActionSettingsBase, \
	((std::vector<MatrixSet>, matrix_types, std::vector<MatrixSet>())) \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	void benchIt(bt::BenchmarkManager const benchmark_manager) const; \
)

template <class class Interface>
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

void MatrixMatrixMultiplication::benchIt(bt::BenchmarkManager const benchmark_manager) const
{
	std::vector<Benchmark::PtrActionBase> result;
	for (auto const& matrix_set : matrix_types)
	{
		for (auto const& size : sizes)
		{
			for (auto const& occupation : occupations)
			{
				for (auto const& interface : interfaces)
				{
					DynamicMatrix dynA;
					if (matrix_set.A == "Matrix<Dense, double>") dynA = std::make_shared<Matrix<Dense, double>>(size, size);
					else if (matrix_set.A == "Matrix<Sparse, double>") dynA = std::make_shared<Matrix<Sparse, double>>(size, size);
					else throw std::runtime_error("Unknown type for matrix_set.A " + matrix_set.A);

					DynamicMatrix dynB;
					if (matrix_set.B == "Matrix<Dense, double>") dynB = std::make_shared<Matrix<Dense, double>>(size, size);
					else if (matrix_set.B == "Matrix<Sparse, double>") dynB = std::make_shared<Matrix<Sparse, double>>(size, size);
					else throw std::runtime_error("Unknown type for matrix_set.B " + matrix_set.B);

					if (interface == "IntelMKL")
					  result.push_back(std::make_shared<MatrixMatrixMultiplicationAction<IntelMKL>>(dynA, dynB));
					else if (interface == "TheBestPolicy")
					  result.push_back(std::make_shared<MatrixMatrixMultiplicationAction<TheBestPolicy>>(dynA, dynB));
					else throw std::runtime_error("Unknown interface " + interface);

					bt::BenchmarkManager::Result result = benchmark_manager.benchIt(Benchmark::PolymorphicAction(ptr_action));
					std::cout << ptr_action->name() << " "
							  << result.nbReplications << " "
							  << result.num_spikes << " "
							  << std::chrono::duration_cast<std::chrono::microseconds>(result.averageTime).count() << " microsec" << std::endl;
				}
			}
		}
	}
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_ */
