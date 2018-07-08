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
        std::string type = "band";
        int rows = 1000;
        int cols = 1000;
        int band_width = 1;
        double value = 1.0;
        bool show_help = false;
        auto cli = clara::Help(show_help)
                 | clara::Opt(matrix_file, "matrix")("Matrix file (default: matrix.dat)")
                 | clara::Opt(type, "type")["-t"]["--type"]("Type of matrix (default: band)")
                 | clara::Opt(rows, "rows")["-r"]["--rows"]("Number of rows (default: 1000)")
                 | clara::Opt(rows, "cols")["-c"]["--cols"]("Number of colums (default: 1000)")
                 | clara::Opt(rows, "band_width")["-b"]["--band-width"]("Number of colums (default: 1)")
                 | clara::Opt(rows, "value")["-v"]["--value"]("Value (default: 1.0)");

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

        Matrix<Dense, double> matrix;

        if (type == "band") {
            matrix = Matrix<Dense, double>{rows, cols, AllFiller<double>{0.0}};
            for (int b = 0; b != band_width; ++b) {
                for (int i = 0; i != rows-b; ++i) {
                    matrix(i+b,i) = value;
                    matrix(i,i+b) = value;
                }
            }
        } else {
            //DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, DiagonalFiller<double>(1e-8)));
            DynamicMatrix F(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(1e-8)));
            DynamicMatrix Z(new Matrix<Dense,double>(1000, 1000, AllFiller<double>(0.0)));

            BlockedDenseMatrix block{{Z,Z,Z,Z},{Z,F,Z,Z},{Z,Z,Z,Z},{Z,Z,Z,Z}};
            matrix = Matrix<Dense, double>{block};
        }

        std::ofstream os(matrix_file, std::ofstream::binary);
        os.write(reinterpret_cast<const char*>(matrix.getDataPointer()), matrix.getSize()*sizeof(double));

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
