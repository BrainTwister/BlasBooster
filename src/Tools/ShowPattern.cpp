#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/PatternGenerator.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/ArgumentParser.h"

using namespace BlasBooster;
namespace bt = BrainTwister;

int main(int argc, char* argv[])
{
    try {

        ScopedTimer scopedTimer("Total time");

        bt::ArgumentParser arg(argc, argv, version,
            {{"matrix", bt::Value<filesystem::path>(), "Matrix filename."}},
            {{"pattern", "p", bt::Value<filesystem::path>("pattern.xpm"), "Matrix pattern filename."},
             {"settings", "s", bt::Value<filesystem::path>("settings.xml"), "Settings for the matrix pattern."}}
        );

        std::cout << "\nBlasBooster " + version + " --- ShowPattern ---\n" << std::endl;

        const Matrix<Dense, double> matrix(arg.get<filesystem::path>("matrix"));

        PatternGenerator(arg.get<filesystem::path>("settings"))(matrix, arg.get<filesystem::path>("pattern"));

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

