#include "ActionSettingsBase.h"
#include "BlasBooster/Core/Threshold.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/Settings.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"
#include "BrainTwister/BenchmarkManager.h"
#include "MatrixMatrixAddition.h"
#include "MatrixMatrixMultiplication.h"
#include "PolymorphicAction.h"
#include <chrono>
#include <iostream>
#include <vector>

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
	(MatrixMatrixAddition) \
)

BLASBOOSTER_SETTINGS(Settings, \
    ((BenchmarkManagerSettings, benchmark_settings, BenchmarkManagerSettings())) \
	((std::vector<std::shared_ptr<ActionSettingsBase>>, actions, std::vector<std::shared_ptr<ActionSettingsBase>>())) \
	((std::vector<std::string>, output, std::vector<std::string>())) \
)

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        ArgumentParser arg(argc, argv, version, {},
            {{"input", "i", Value<filesystem::path>("input.yml"), "Input file defining the benchmark settings."},
             {"output", "o", Value<filesystem::path>("output.yml"), "Output file containing the benchmark results."}}
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
