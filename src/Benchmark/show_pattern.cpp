#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/MatrixFileIO.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "BlasBooster/Core/PatternGenerator.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BlasBooster/Utilities/ScopedTimer.h"
#include "BlasBooster/Utilities/Version.h"
#include "BrainTwister/JSON.h"
#include "BrainTwister/Record.h"
#include "clara.hpp"
#include <iostream>

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
        int border_width = 0;
        bool show_help = false;
        auto cli = clara::Help(show_help)
        		 | clara::Arg(matrix_file, "matrix")("Matrix file (*.xml)").required()
                 | clara::Opt(settings_file, "settings")["-s"]["--settings"]("Settings file (*.xml)")
                 | clara::Opt(pattern_file, "pattern")["-p"]["--pattern"]("Pattern file (default: pattern.xpm)")
				 | clara::Opt(pattern_type, "type")["-t"]["--pattern-type"]("Type of pattern (elements or type-blocks)")
		         | clara::Opt(border_width, "width")["-w"]["--border_width"]("Number of points for the border (default: 0)");

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
            auto dim_matrix = generateDimensionMatrix(block_matrix);

            std::cout << "type matrix: " << type_matrix << std::endl;
            std::cout << "dimension matrix: " << dim_matrix << std::endl;

            Matrix<Dense, double> type_block_matrix(matrix.getNbRows(), matrix.getNbColumns());

            typedef TypeMatrix::parameter P;
			P::IndexType sub_row_offset(0), sub_row_offset_tmp(0), sub_column_offset(0);

            typedef Cursor<TypeMatrix, Direction::Row> TypeRowCursor;
            typedef Cursor<TypeRowCursor, Direction::Column> TypeColumnCursor;
            typedef Cursor<DimensionMatrix, Direction::Row> DimRowCursor;
            typedef Cursor<DimRowCursor, Direction::Column> DimColumnCursor;
            DimRowCursor dim_row_cur(dim_matrix, 0), dim_row_end(dim_matrix, dim_matrix.getNbRows());
            for (TypeRowCursor type_row_cur(type_matrix, 0), type_row_end(type_matrix, type_matrix.getNbRows());
                 type_row_cur != type_row_end; ++type_row_cur, ++dim_row_cur)
            {
            	DimColumnCursor dim_column_cur(dim_matrix, dim_row_cur.begin()), dim_column_end(dim_matrix, dim_row_cur.end());
                for (TypeColumnCursor type_column_cur(type_matrix, type_row_cur.begin()), type_column_end(type_matrix, type_row_cur.end());
                     type_column_cur != type_column_end; ++type_column_cur, ++dim_column_cur)
                {
                    typedef Matrix<Dense, double, Parameter<typename P::IndexType, typename P::orientation, typename P::SizeType, LeadingDimension>> SubMatrix;

                    SubMatrix sub_matrix(type_block_matrix, (*dim_column_cur).first, (*dim_column_cur).second, sub_row_offset, sub_column_offset);

                    AllFiller<double>(std::pow(10, -1.0 * (*type_column_cur)))(sub_matrix);

                    for (int i = 0; i != border_width; ++i) {
                    	for (size_t j = 0; j != (*dim_column_cur).first; ++j) sub_matrix(j,i) = 0.0;
                    	for (size_t j = border_width; j != (*dim_column_cur).second; ++j) sub_matrix(i,j) = 0.0;
                    }

                    // TODO: rowOffset is ideally determined one time (all submatrices in a column have the same row size).
                    // But I don't know yet how to determine the offset in the outer loop.
                    sub_row_offset_tmp = (*dim_column_cur).first;
                    sub_column_offset += (*dim_column_cur).second;
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
