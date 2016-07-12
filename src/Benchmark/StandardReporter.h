#ifndef SRC_BENCHMARK_STANDARDREPORTER_H_
#define SRC_BENCHMARK_STANDARDREPORTER_H_

#include <iostream>
#include <string>
#include "BlasBooster/Utilities/Settings.h"
#include "ReporterBase.h"

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS_DERIVED(StandardReporter, ReporterBase, \
	((int, verbosity, 1)), \
	void log(std::string const& message) const; \
)

void StandardReporter::log(std::string const& message) const
{
	std::cout << message << std::endl;
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_STANDARDREPORTER_H_ */
