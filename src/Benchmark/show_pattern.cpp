#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/PatternGenerator.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "clara.hpp"

using namespace BlasBooster;

BRAINTWISTER_RECORD(BlockedMatrixGeneratorSettings, \
    ((int, min_block_size, 200)) \
    ((int, max_block_size, 1000)) \
    ((ThresholdSettings, threshold, ThresholdSettings{})) \
);

BRAINTWISTER_RECORD(Settings, \
    ((PatternGenerator::Settings, pattern_generator_settings, PatternGenerator::Settings())) \
    ((BlockedMatrixGeneratorSettings, blocked_matrix_generator_settings, BlockedMatrixGeneratorSettings())) \
);

int main(int argc, char* argv[])
{
    try {

        ScopedTimer scopedTimer("Total time");

        std::cout << "\nBlasBooster " + version + " ShowPattern\n" << std::endl;

        std::string matrix_file;
        std::string settings_file = "";
		std::string pattern_file = "pattern.xpm";
		std::string pattern_type = "elements";
        bool show_help = false;
        auto cli = clara::Help(show_help)
        		 | clara::Arg(matrix_file, "matrix")("Matrix file (*.xml)").required()
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (*.xml)")
                 | clara::Opt(pattern_file, "pattern")["-p"]["--pattern"]("Pattern file (default: pattern.xpm)")
				 | clara::Opt(pattern_type, "pattern_type")["-t"]["--pattern-type"]("Type of pattern (elements or type-blocks)");

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
        Settings settings{JSON{settings_str}};

        PatternGenerator pattern_generator{settings.pattern_generator_settings};

        if (pattern_type == "elements") {

            pattern_generator(matrix, pattern_file);

        } else if (pattern_type == "type-blocks") {

        	auto bset = settings.blocked_matrix_generator_settings;
            auto block_sizes = BlockSizeGenerator(bset.min_block_size, bset.max_block_size)(matrix);
            auto block_matrix = BlockedMatrixGenerator()(matrix, block_sizes.first, block_sizes.second, bset.threshold);
            auto type_matrix = generateTypeMatrix(block_matrix);

            Matrix<Dense, double> type_block_matrix(matrix.getNbRows(), matrix.getNbColumns());

            typedef TypeMatrix::parameter P;
			P::IndexType sub_row_offset(0), sub_row_offset_tmp(0), sub_column_offset(0);

            typedef Cursor<TypeMatrix, Direction::Row> RowCursor;
            typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
            for (RowCursor row_cur(type_matrix, 0), row_end(type_matrix, type_matrix.getNbRows()); row_cur != row_end; ++row_cur)
            {
                for (ColumnCursor column_cur(type_matrix, row_cur.begin()), column_end(type_matrix, row_cur.end()); column_cur != column_end; ++column_cur)
                {
                    typedef Matrix<Dense, double, Parameter<typename P::IndexType, typename P::orientation, typename P::SizeType, LeadingDimension>> SubMatrix;

                    SubMatrix sub_matrix(type_block_matrix, getNbRows(*columnCur), getNbColumns(*columnCur), sub_row_offset, sub_column_offset);

                    AllFiller<double>(std::pow(10, *column_cur))(sub_matrix);

                    // TODO: rowOffset is ideally determined one time (all submatrices in a column have the same row size).
                    // But I don't know yet how to determine the offset in the outer loop.
                    sub_row_offset_tmp = getNbRows(*column_cur);
                    sub_column_offset += getNbColumns(*column_cur);
                }
                sub_row_offset += sub_row_offset_tmp;
                sub_column_offset = 0;
            }

            pattern_generator(type_block_matrix, pattern_file);

        } else {
        	throw std::runtime_error("Unkown pattern_type: " + pattern_type);
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

    std::cout << "\nBlasBooster successfully finished. Have a nice day.\n" << std::endl;

}
