#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/PatternGenerator.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/XML.h"
#include "clara.hpp"

using namespace BlasBooster;
using namespace clara;

int main(int argc, char* argv[])
{
    try {

        ScopedTimer scopedTimer("Total time");

        std::cout << "\nBlasBooster " + version + " ShowPattern\n" << std::endl;

        std::string matrix_file, settings_file, pattern_file;
        bool show_help = true;
        auto cli = Help(show_help)
        		 | Opt(matrix_file, "matrix")
                      ["-m"]["--matrix"]
                      ("Matrix filename")
                 | Opt(settings_file, "settings")
                      ["-s"]["--settings"]
                      ("Settings filename")
                 | Opt(pattern_file, "pattern")
                      ["-p"]["--pattern"]
                      ("Pattern filename");

        auto result = cli.parse(Args(argc, argv));
        if(!result) {
            std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
            return 1;
        }

        const Matrix<Dense, double> matrix(matrix_file);

        std::ifstream ifs{settings_file};
        std::string settings_str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        PatternGenerator{XML{settings_str}}(matrix, pattern_file);

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
