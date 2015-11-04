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
BLASBOOSTER_SETTINGS( ActionSettings,\
	(( MatrixType, matrix_type, MatrixType::dense ))\
	(( int, nbThreads, 1 ))\
	(( ThresholdSettings, thresholdSettings, ThresholdSettings() ))\
)

BLASBOOSTER_SETTINGS( Settings,\
	(( bt::BenchmarkManager::Settings, benchmark_manager_settings, bt::BenchmarkManager::Settings() ))
	(( std::vector<MatrixSet>, matrix_set_list, std::vector<MatrixSet>() ))
	(( std::vector<ActionSettings>, action_settings_list, std::vector<ActionSettings>() ))
)
#endif

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        bt::ArgumentParser arg(argc, argv, version, {},
            {{"input", "i", bt::Value<filesystem::path>("input.xml"), "Input file defining the benchmark settings."},
             {"output", "o", bt::Value<filesystem::path>("output.xml"), "Output file containing the benchmark results."}}
        );

#if 0
        const Settings settings(arg.get<filesystem::path>("settings"));

        for (auto const& matrix_set : matrix_set_list)
        {
            bt::BenchmarkManager benchmark_manager(settings.benchmark_manager_settings);
            for (auto const& action : settings.action_list)
            {
                benchmark_manager.benchIt(action);
            }
        }



        const Threshold threshold(settings.thresholdSettings);

        std::cout << "Number of threads: " << settings.nbThreads << std::endl;

        BlasBooster::mkl_set_num_threads(settings.nbThreads);
        BlasBooster::openblas_set_num_threads(settings.nbThreads);

        const Matrix<Dense, double> refA(arg.get<filesystem::path>("matrixA"));
        const Matrix<Dense, double> refB(arg.get<filesystem::path>("matrixB"));
        Matrix<Dense, double> refC;

        bt::BenchmarkManager benchmark_manager;
        for (auto const& action : settings.action_list) benchmark_manager.benchIt(action);


        {
            ScopedTimer scopedTimer("Intel MKL dgemm");
            refC = (refA * refB).template execute<IntelMKL>();
        }
        if (settings.openBLASDouble) {
            ScopedTimer scopedTimer("OpenBLAS dgemm");
            Matrix<Dense, double> C = (refA * refB).template execute<OpenBLAS>();
        }
        if (settings.intelMKLSingle) {
            ScopedTimer scopedTimer("Intel MKL sgemm");
            Matrix<Dense, float> A(refA);
            Matrix<Dense, float> B(refB);
            Matrix<Dense, float> C = (A * B).template execute<IntelMKL>();

            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(C - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(C - refC) << std::endl;
        }
        if (settings.sparseDouble) {
            ScopedTimer scopedTimer("sparse double");
            Matrix<Sparse, double> A(refA, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> B(refB, AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()));
            Matrix<Sparse, double> C = A * B;

            Matrix<Dense, double> denseC(C);
            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
        }
        if (settings.blockedTheBestPolicy) {
            ScopedTimer scopedTimer("blocked multiplication");

            std::unique_ptr<ScopedTimer> ptrScopedTimer(new ScopedTimer("blocked multiplication, block size"));
            BlockSizeGenerator block_size_generator(100, 400);
            auto blockSizeA = block_size_generator(refA);
            auto blockSizeB = block_size_generator(refB);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, blocking"));
            BlockedDenseMatrix A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, settings.thresholdSettings);
            BlockedDenseMatrix B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, settings.thresholdSettings);

            //std::cout << *(std::static_pointer_cast<MultipleMatrix<Matrix<Sparse, double>, Matrix<Dense, float>>>(A(0,0))->getMatrix1().endOffset()-1) << std::endl;
            std::cout << generateTypeMatrix(A) << std::endl;
            std::cout << generateDimensionMatrix(A) << std::endl;

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, mult"));
            BlockedDenseMatrix C = (A * B).template execute<TheBestPolicy>();

            Matrix<Dense, double> denseC(C);
            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
        }
#endif
    } catch ( BlasBoosterException const& e ) {
        std::cout << "BlasBooster exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    } catch ( std::exception const& e ) {
        std::cout << "Standard exception: " << e.what() << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    } catch ( ... ) {
        std::cout << "Unknown exception." << std::endl;
        std::cout << "Program was aborted." << std::endl;
        return 1;
    }

    std::cout << "\n BlasBooster successfully finished. Have a nice day.\n" << std::endl;

}
