#ifndef SRC_BENCHMARK_REPORTERMANAGER_H_
#define SRC_BENCHMARK_REPORTERMANAGER_H_

#include <string>
#include "ReporterBase.h"

namespace BlasBooster {
namespace Benchmark {

BLASBOOSTER_SETTINGS_DERIVED(ReporterManager, ReporterBase, \
    ((std::vector<std::shared_ptr<ReporterBase>>, reporters, std::vector<std::shared_ptr<ReporterBase>>())), \
	void log(std::string const& message) const; \
)

void ReporterManager::log(std::string const& message) const
{
	for (auto const& reporter : reporters) reporter->log(message);
}

} // namespace Benchmark
} // namespace BlasBooster

#endif /* SRC_BENCHMARK_REPORTERMANAGER_H_ */
