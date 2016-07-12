#include <stddef.h>
#include <iostream>
#include <string>
#include <vector>
#include "BrainTwister/ArgumentParser.h"
#include "BrainTwister/BenchmarkManager.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/Settings.h"
#include "BlasBooster/Utilities/Version.h"
#include "MatrixMatrixMultiplication.h"
#include "ReporterBase.h"
#include "StandardReporter.h"

using namespace BlasBooster;
using namespace BlasBooster::Benchmark;
using namespace BrainTwister;

BLASBOOSTER_SETTINGS(BenchmarkManagerSettings, \
    ((size_t, min_replications, 3)) \
    ((size_t, min_execution_time_in_milliseconds, 1000)) \
    ((double, spike_detection, 0.1)) \
)

BLASBOOSTER_SETTINGS_REGISTER(ActionSettingsBase, \
	(MatrixMatrixMultiplication) \
)

BLASBOOSTER_SETTINGS_REGISTER(ReporterBase, \
	(StandardReporter) \
)

BLASBOOSTER_SETTINGS(Settings, \
    ((BenchmarkManagerSettings, benchmark_settings, BenchmarkManagerSettings())) \
	((std::vector<std::shared_ptr<ActionSettingsBase>>, actions, std::vector<std::shared_ptr<ActionSettingsBase>>())) \
	((std::vector<std::shared_ptr<ReporterBase>>, reporters, std::vector<std::shared_ptr<ReporterBase>>())) \
)

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        ArgumentParser arg(argc, argv, version, {},
            {{"input", "i", Value<filesystem::path>("input.yml"), "Input file (xml, json, or yml) defining the benchmark settings."}}
        );

        const Settings settings(arg.get<filesystem::path>("input"));
        const BenchmarkManager benchmark_manager(BenchmarkManager::Settings(
        	settings.benchmark_settings.min_replications,
			std::chrono::milliseconds(settings.benchmark_settings.min_execution_time_in_milliseconds),
        	settings.benchmark_settings.spike_detection
		));

        for (auto const& action_settings : settings.actions)
        {
        	action_settings->execute(benchmark_manager);
        }
    }
    catch (BlasBoosterException const& e)
    {
        std::cout << "BlasBooster exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    }
    catch (std::exception const& e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cout << "Unknown exception." << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    }

    std::cout << "\nBlasBooster successfully finished. Have a nice day.\n" << std::endl;
}
