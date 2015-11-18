#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Settings.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"
#include "BrainTwister/BenchmarkManager.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace BlasBooster;
namespace bt = BrainTwister;

#if 0
BLASBOOSTER_SETTINGS(ActionSettings,\
    ((std::vector<MatrixSet>, matrix_set_list, std::vector<MatrixSet>()))\
	((MatrixType, matrix_type, MatrixType::dense))((int, nbThreads, 1))\
	((ThresholdSettings, thresholdSettings, ThresholdSettings()))\
	)

BLASBOOSTER_SETTINGS(Settings,\
    ((bt::BenchmarkManager::Settings, benchmark_manager_settings, bt::BenchmarkManager::Settings()))\
	((std::vector<ActionSettings>, action_settings_list, std::vector<ActionSettings>()))\
)
#endif

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        bt::ArgumentParser arg(argc, argv, version, {},
            {{"input", "i", bt::Value<filesystem::path>("input.xml"), "Input file defining the benchmark settings."},
             {"output", "o", bt::Value<filesystem::path>("output.xml"), "Output file containing the benchmark results."}}
        );

#if 0
        const Settings settings(arg.get<filesystem::path>("input"));
        const bt::BenchmarkManager benchmark_manager(settings.benchmark_manager_settings);

        for (auto const& action : settings.action_settings_list)
        {
            benchmark_manager.benchIt(action);
        }
#endif
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
