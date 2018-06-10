#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Version.h"
#include <fstream>

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Matrix Generator\n" << std::endl;

        //DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, DiagonalFiller<double>(1e-8)));
        DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(1e-8)));
        DynamicMatrix Z(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(0.0)));


        BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
        const Matrix<Dense, double> A{block};

        std::ofstream os("matrix.dat", std::ofstream::binary);
        auto data = A.getDataPointer();
        for (size_t i = 0; i != A.getSize(); ++i) os << data[i];

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
