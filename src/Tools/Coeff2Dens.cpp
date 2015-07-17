#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Transposition.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"
#include <iostream>
#include <iomanip>
#include <memory>

using namespace BlasBooster;
namespace bt = BrainTwister;

int main(int argc, char* argv[])
{
    try {

        ScopedTimer scopedTimer("Total time");

        bt::ArgumentParser arg(argc, argv, version,
            {{"C", bt::Value<filesystem::path>("C.mat"), "Coefficient matrix C."},
             {"Pocc", bt::Value<filesystem::path>("Pocc.mat"), "Occupied density matrix Pocc."}},
            {{"threads", "t", bt::Value<int>(1), "Number of threads."}}
        );

        std::cout << "\nBlasBooster " + version + " --- Coeff2Dens ---\n" << std::endl;

        int nbThreads = arg.get<int>("threads");
        std::cout << "Number of threads: " << nbThreads << std::endl;

        BlasBooster::mkl_set_num_threads(nbThreads);
        BlasBooster::openblas_set_num_threads(nbThreads);

        Matrix<Dense,double> Cocc;
        //read(Cocc, arg.get<filesystem::path>("C"));

        auto CoccT = transpose(Cocc);
        Matrix<Dense,double> Pocc = (Cocc * CoccT).template execute<IntelMKL>();

        //write(Pocc, arg.get<filesystem::path>("Pocc"));

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

