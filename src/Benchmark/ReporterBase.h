// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_REPORTERBASE_H_
#define SRC_BENCHMARK_REPORTERBASE_H_

#include <string>
#include "BlasBooster/Utilities/Settings.h"

namespace BlasBooster {
namespace Benchmark {

/// Abstract base for benchmark reporter
BLASBOOSTER_SETTINGS_BASE_NO_MEMBERS(ReporterBase, \
	virtual void log(std::string const& message) const = 0; \
)

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_REPORTERBASE_H_ */
