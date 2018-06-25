#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/PatternGenerator.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/JSON.h"
#include "clara.hpp"

using namespace BlasBooster;

int main(int argc, char* argv[])
{
    try {

        ScopedTimer scopedTimer("Total time");

        std::cout << "\nBlasBooster " + version + " ShowPattern\n" << std::endl;

        std::string matrix_file;
        std::string settings_file = "";
		std::string pattern_file = "pattern.xpm";
        bool show_help = false;
        auto cli = clara::Help(show_help)
        		 | clara::Arg(matrix_file, "matrix")("Matrix file (*.xml)").required()
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (*.xml)")
                 | clara::Opt(pattern_file, "pattern")["-p"]["--pattern"]("Pattern file (default: pattern.xpm)");

        auto r = cli.parse(clara::Args(argc, argv));
        if(!r)
        {
    	    std::cerr << cli << std::endl;
            std::cerr << "Error in command line: " << r.errorMessage() << std::endl;
            return 1;
        }
        if (show_help)
        {
    	    std::cerr << cli << std::endl;
            return 0;
        }

        std::cout << "matrix_file: " << matrix_file << std::endl;
        const Matrix<Dense, double> matrix(matrix_file);

        std::ifstream ifs{settings_file};
        std::string settings_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        std::cout << "pattern_file: " << pattern_file << std::endl;
        PatternGenerator{JSON{settings_str}}(matrix, pattern_file);

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

    std::cout << "\nBlasBooster successfully finished. Have a nice day.\n" << std::endl;

}
