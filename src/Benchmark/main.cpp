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
namespace bt = BrainTwister;

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
			std::chrono::milliseconds(settings.benchmark_manager_settings.min_execution_time_in_milliseconds),
        	settings.benchmark_manager_settings.spike_detection
		));

        for (auto const& action_settings : settings.actions)
        {
        	for (auto const& ptr_action : action_settings->get_actions())
        	{
                bt::BenchmarkManager::Result result = benchmark_manager.benchIt(Benchmark::PolymorphicAction(ptr_action));
        	    std::cout << ptr_action->name() << " "
      	    		      << result.nbReplications << " "
      	    		      << result.num_spikes << " "
        	    		  << std::chrono::duration_cast<std::chrono::microseconds>(result.averageTime).count() << " microsec" << std::endl;
        	}
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
