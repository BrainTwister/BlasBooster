// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef SRC_BENCHMARK_ACTIONSETTINGSBASE_H_
#define SRC_BENCHMARK_ACTIONSETTINGSBASE_H_

#include "ActionBase.h"
#include "BlasBooster/Core/Threshold.h"
#include "BlasBooster/Utilities/Settings.h"

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS_BASE(ActionSettingsBase, \
	((ThresholdSettings, threshold_settings, ThresholdSettings())), \
	virtual std::vector<Benchmark::PtrActionBase> get_actions() const = 0; \
)

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_ACTIONSETTINGSBASE_H_ */
