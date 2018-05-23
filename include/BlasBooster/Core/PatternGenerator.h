#pragma once

#include "BlasBooster/Utilities/FileIO.h"
#include "BlasBooster/Utilities/Filesystem.h"
#include "BrainTwister/Record.h"
#include "Cursor.h"
#include "DenseMatrix.h"
#include <fstream>
#include <string>
#include <vector>

namespace BlasBooster {

/// Create an xpm image file of the matrix pattern
class PatternGenerator
{
public:

    BRAINTWISTER_RECORD(Color, \
		((std::string, index, "")) \
		((std::string, color, "")) \
		((double, threshold, 0.0)) \
	);

    BRAINTWISTER_RECORD(Settings, \
        ((std::vector<Color>, palette, std::vector<Color>())) \
		((std::string, background_index, "")) \
		((std::string, background_color, "")) \
	);

    PatternGenerator(Settings const& settings = Settings())
     : settings(settings)
    {}

    template <class T, class P>
    void operator()(Matrix<Dense,T,P> const& matrix, filesystem::path const& file) const;

private:

    Settings settings;

};

template <class T, class P>
void PatternGenerator::operator()(Matrix<Dense,T,P> const& matrix, filesystem::path const& file) const
{
    std::ofstream outfile(file.string());

    // <width> <height> <colors> <char on pixel>
    outfile << "/* XPM */\nstatic char * matrix_xpm[] = {\n\""
            << matrix.getNbColumns() << " "
            << matrix.getNbRows() << " "
            << settings.palette.size() + 1 << " "
            << "1\","
            << std::endl;

    for(auto const& color : settings.palette)
    {
        outfile << "\""
                << color.index
                << "\tc #"
                << color.color
                << "\","
                << std::endl;
    }
    outfile << "\""
            << settings.background_index
            << "\tc #"
            << settings.background_color
            << "\","
            << std::endl;

    outfile << "/* Data section */" << std::endl;

    T absValue;

    typedef Cursor<const Matrix<Dense,T,P>, Direction::Row> RowCursor;
    typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
    RowCursor rowLast(matrix,matrix.getNbRows());
    --rowLast;
    for ( RowCursor rowCur(matrix,0), rowEnd(matrix,matrix.getNbRows());
        rowCur != rowEnd; ++rowCur )
    {
        outfile << "\"";
        for (ColumnCursor columnCur(matrix,rowCur.begin()), columnEnd(matrix,rowCur.end());
            columnCur != columnEnd; ++columnCur)
        {
            absValue = std::abs(*columnCur);
            std::string pixel(settings.background_index);

            for(auto const& color : settings.palette)
            {
                if (absValue >= color.threshold)
                {
                    pixel = color.index;
                    break;
                }
            }
            outfile << pixel;
        }
        if ( rowCur == rowLast ) outfile << "\"";
        else outfile << "\"," << std::endl;
    }
    outfile << "};" << std::endl;
}

} // namespace BlasBooster
