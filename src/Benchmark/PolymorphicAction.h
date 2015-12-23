// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_POLYMORPHICACTION_H_
#define SRC_BENCHMARK_POLYMORPHICACTION_H_

namespace BlasBooster {
namespace Benchmark {

/// Abstract base for polymorphic benchmark object
struct ActionBase
{
	virtual ~ActionBase();
	virtual void initialize() = 0;
	virtual void execute() = 0;
	virtual void check() = 0;
};

/// Provide a general benchmark action object by ...
template <class Base>
struct PolymorphicAction
{
	PolymorphicAction(std::shared_ptr<Base> ptr_base)
	 : ptr_base(ptr_base)
	{}

	void initialize() {
		ptr_base->initialize();
	}

	void execute() {
		ptr_base->execute();
	}

	void check() {
		ptr_base->check();
	}

	std::shared_ptr<Base> ptr_base;
};

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_POLYMORPHICACTION_H_ */
