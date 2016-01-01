// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_ACTIONBASE_H_
#define SRC_BENCHMARK_ACTIONBASE_H_

#include <memory>
#include <string>

namespace BlasBooster {
namespace Benchmark {

/// Abstract base for polymorphic benchmark object
struct ActionBase
{
	virtual ~ActionBase() {}
	virtual std::string name() const = 0;
	virtual void initialize() const = 0;
	virtual void execute() const = 0;
	virtual void check() const = 0;
};

using PtrActionBase = std::shared_ptr<ActionBase>;

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_ACTIONBASE_H_ */
