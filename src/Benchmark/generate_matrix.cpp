#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Version.h"
#include "clara.hpp"
#include <fstream>

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        std::cout << "\nBlasBooster " + version + " Matrix Generator\n" << std::endl;

        std::string matrix_file = "matrix.dat";
		std::string pattern_type = "elements";
        bool show_help = false;
        auto cli = clara::Help(show_help)
        		 | clara::Opt(matrix_file, "matrix")("Matrix file (default: matrix.dat)")
				 | clara::Opt(pattern_type, "type")["-t"]["--pattern-type"]("Type of pattern (elements or type-blocks)");

        auto cli_result = cli.parse(clara::Args(argc, argv));
        if(!cli_result)
        {
    	    std::cerr << cli << std::endl;
            std::cerr << "Error in command line: " << cli_result.errorMessage() << std::endl;
            return 1;
        }
        if (show_help)
        {
    	    std::cerr << cli << std::endl;
            return 0;
        }

        //DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, DiagonalFiller<double>(1e-8)));
        DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(1e-8)));
        DynamicMatrix Z(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(0.0)));

        BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
        const Matrix<Dense, double> A{block};

        std::ofstream os(matrix_file, std::ofstream::binary);
        os.write(reinterpret_cast<const char*>(A.getDataPointer()), A.getSize()*sizeof(double));

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
