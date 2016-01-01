// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_POLYMORPHICACTION_H_
#define SRC_BENCHMARK_POLYMORPHICACTION_H_

#include "ActionBase.h"

namespace BlasBooster {
namespace Benchmark {

/// Provide a general benchmark action object by ...
struct PolymorphicAction
{
	PolymorphicAction(PtrActionBase ptr_base)
	 : ptr_base(ptr_base)
	{}

	std::string name() const {
		return ptr_base->name();
	}

	void initialize() const {
		ptr_base->initialize();
	}

	void execute() const {
		ptr_base->execute();
	}

	void check() const {
		ptr_base->check();
	}

private:

	PtrActionBase ptr_base;

};

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_POLYMORPHICACTION_H_ */
