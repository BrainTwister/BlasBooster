#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include <iostream>

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        std::cout << "BlasBooster " + version + " Benchmark" << std::endl;

    	const Matrix<Dense, double> refA;
        const Matrix<Dense, double> refB;
        Matrix<Dense, double> refC;

        {
            ScopedTimer scopedtimer("Intel MKL dgemm");
            refC = refA * refB;
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

