// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_
#define SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_

namespace BlasBooster {
namespace BenchmarkAction {

template <class Interface>
struct MatrixMatrixMultiplication
{
	Action_MatrixMatrixMultiplication()
	 : settings_(), ptrA_(), ptrB_(), ptrC_()
	{}

	Action_MatrixMatrixMultiplication( const Action_MatrixMatrixMultiplicationSettings& settings )
	 : settings_(settings), ptrA_(), ptrB_(), ptrC_()
	{}

	void initialize() {}

	void execute() {}

	void check() {}

};

} // namespace BenchmarkAction
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_MATRIXMATRIXMULTIPLICATION_H_ */
