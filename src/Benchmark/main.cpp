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
#include <iostream>
#include <iomanip>
#include <memory>
// tmp
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace BlasBooster;
namespace bt = BrainTwister;

BLASBOOSTER_SETTINGS( Settings,\
	(( bool, openBLASDouble, true ))\
	(( bool, intelMKLSingle, true ))\
	(( bool, sparseDouble, true ))\
	(( bool, blockedTheBestPolicy, true ))\
	(( int, nbThreads, 1 ))\
	(( ThresholdSettings, thresholdSettings, ThresholdSettings() ))\
)

int main(int argc, char* argv[])
{
    try {

        bt::ArgumentParser arg(argc, argv, version,
            {{"matrixA", bt::Value<filesystem::path>(), "File for matrix A."},
             {"matrixB", bt::Value<filesystem::path>(), "File for matrix B."}},
            {{"settings", "s", bt::Value<filesystem::path>("settings.xml"), "File for benchmark settings."}}
        );

        std::cout << "\nBlasBooster " + version + " --- Benchmark ---\n" << std::endl;

        std::ifstream ifs(arg.get<filesystem::path>("settings").string());
        if (!ifs) throw std::runtime_error("Error opening file " + arg.get<filesystem::path>("settings").string());
        boost::property_tree::ptree tree;
        boost::property_tree::read_xml(ifs, tree);
        Settings settings(tree);

        std::cout << "Number of threads: " << settings.nbThreads << std::endl;

        BlasBooster::mkl_set_num_threads(settings.nbThreads);
        BlasBooster::openblas_set_num_threads(settings.nbThreads);

        Threshold threshold(settings.thresholdSettings);

        const Matrix<Dense, double> refA(arg.get<filesystem::path>("matrixA"));
        const Matrix<Dense, double> refB(arg.get<filesystem::path>("matrixB"));
        Matrix<Dense, double> refC;

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
            auto blockSizeA = BlockSizeGenerator(100, 400)(refA);
            auto blockSizeB = BlockSizeGenerator(100, 400)(refB);

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, blocking"));
            BlockedDenseMatrix A = BlockedMatrixGenerator()(refA, blockSizeA.first, blockSizeA.second, settings.thresholdSettings);
            BlockedDenseMatrix B = BlockedMatrixGenerator()(refB, blockSizeB.first, blockSizeB.second, settings.thresholdSettings);

            std::cout << generateTypeMatrix(A) << std::endl;
            std::cout << generateDimensionMatrix(A) << std::endl;

            ptrScopedTimer.reset(new ScopedTimer("blocked multiplication, mult"));
            BlockedDenseMatrix C = (A * B).template execute<TheBestPolicy>();

            Matrix<Dense, double> denseC(C);
            std::cout << std::scientific << std::setprecision(6);
            std::cout << "max-norm = " << norm<NormMax>(denseC - refC) << std::endl;
            std::cout << "  2-norm = " << norm<NormTwo>(denseC - refC) << std::endl;
        }

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
