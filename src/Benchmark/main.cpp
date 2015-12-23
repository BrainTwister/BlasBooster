#include "BlasBooster/Core/Threshold.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/Settings.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"
#include "BrainTwister/BenchmarkManager.h"
#include <chrono>
#include <iostream>
#include <vector>

using namespace BlasBooster;
namespace bt = BrainTwister;

BLASBOOSTER_SETTINGS(BenchmarkManagerSettings, \
    ((size_t, min_replications, 3)) \
    ((size_t, min_execution_time_in_seconds, 1)) \
    ((double, spike_detection, 0.1)) \
)

BLASBOOSTER_SETTINGS_BASE(ActionSettingsBase, \
	((ThresholdSettings, threshold_settings, ThresholdSettings())), \
	virtual void execute() const = 0; \
)

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixAddition, ActionSettingsBase, \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	virtual void execute() const; \
)

void MatrixMatrixAddition::execute() const
{
	std::cout << "Here we are: MatrixMatrixAddition" << std::endl;
}

BLASBOOSTER_SETTINGS_DERIVED(MatrixMatrixMultiplication, ActionSettingsBase, \
	((std::vector<size_t>, sizes, std::vector<size_t>())) \
	((std::vector<double>, occupations, std::vector<double>())) \
    ((std::vector<std::string>, interfaces, std::vector<std::string>())), \
	virtual void execute() const; \
)

void MatrixMatrixMultiplication::execute() const
{
	std::cout << "Here we are: MatrixMatrixMultiplication" << std::endl;
}

BLASBOOSTER_SETTINGS_REGISTER(ActionSettingsBase, \
	(MatrixMatrixAddition) \
	(MatrixMatrixMultiplication) \
)

BLASBOOSTER_SETTINGS(Settings, \
    ((BenchmarkManagerSettings, benchmark_manager_settings, BenchmarkManagerSettings())) \
	((std::vector<std::shared_ptr<ActionSettingsBase>>, actions, std::vector<std::shared_ptr<ActionSettingsBase>>())) \
)

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        bt::ArgumentParser arg(argc, argv, version, {},
            {{"input", "i", bt::Value<filesystem::path>("input.xml"), "Input file defining the benchmark settings."},
             {"output", "o", bt::Value<filesystem::path>("output.xml"), "Output file containing the benchmark results."}}
        );

        const Settings settings(arg.get<filesystem::path>("input"));
        const bt::BenchmarkManager benchmark_manager(bt::BenchmarkManager::Settings(
        	settings.benchmark_manager_settings.min_replications,
			std::chrono::seconds(settings.benchmark_manager_settings.min_execution_time_in_seconds),
        	settings.benchmark_manager_settings.spike_detection
		));

        for (auto const& action : settings.actions)
        {
        	action->execute();
            //benchmark_manager.benchIt(action);
        	//for (auto const& interface : action->interfaces) std::cout << interface << std::endl;
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

    std::cout << "\n BlasBooster successfully finished. Have a nice day.\n" << std::endl;
}
