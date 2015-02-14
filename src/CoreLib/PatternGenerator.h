#ifndef PATTERNGENERATOR_H_
#define PATTERNGENERATOR_H_

#include "Cursor.h"
#include "DenseMatrix.h"
#include <boost/filesystem.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <fstream>
#include <string>
#include <vector>

namespace BlasBooster {

/// Create pattern image of a matrix
class PatternGenerator
{
public:

    class Color {
    public:
        Color()
         : index_(), color_(), threshold_(0.0)
        {}
        Color( const std::string& index, const std::string& color, double threshold )
         : index_(index), color_(color), threshold_(threshold)
        {}
        std::string index_;
        std::string color_;
        double threshold_;
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("Index", index_);
            ar & boost::serialization::make_nvp("Color", color_);
            ar & boost::serialization::make_nvp("Threshold", threshold_);
        }
    };

    class Settings {
    public:
        typedef std::vector<Color> Palette;
        Palette palette_;
        std::string backgroundIndex_;
        std::string backgroundColor_;
    private:
        friend class boost::serialization::access;
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("Palette", palette_);
            ar & boost::serialization::make_nvp("BackgroundIndex", backgroundIndex_);
            ar & boost::serialization::make_nvp("BackgroundColor", backgroundColor_);
        }
    };

    PatternGenerator( const Settings& settings )
    : settings_(settings)
    {}

    template <class T,class P>
    void generate(Matrix<Dense,T,P> const& matrix, boost::filesystem::path const& file);

private:

    Settings settings_;

};

template<class T,class P>
void PatternGenerator::generate(Matrix<Dense,T,P> const& matrix, boost::filesystem::path const& file)
{
    std::ofstream outfile(file.string());

    // <width> <height> <colors> <char on pixel>
    outfile << "/* XPM */\nstatic char * matrix_xpm[] = {\n\""
            << matrix.getNbColumns() << " "
            << matrix.getNbRows() << " "
            << settings_.palette_.size() + 1 << " "
            << "1\","
            << std::endl;

    for( Settings::Palette::const_iterator iterColorCur(settings_.palette_.begin()), iterColorEnd(settings_.palette_.end());
        iterColorCur != iterColorEnd; ++iterColorCur )
    {
        outfile << "\""
                << iterColorCur->index_
                << "\tc #"
                << iterColorCur->color_
                << "\","
                << std::endl;
    }
    outfile << "\""
            << settings_.backgroundIndex_
            << "\tc #"
            << settings_.backgroundColor_
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
            std::string pixel(settings_.backgroundIndex_);

            for( Settings::Palette::const_iterator iterColorCur(settings_.palette_.begin()), iterColorEnd(settings_.palette_.end());
                iterColorCur != iterColorEnd; ++iterColorCur )
            {
                if ( absValue >= iterColorCur->threshold_ )
                {
                    pixel = iterColorCur->index_;
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

#endif /* PATTERNGENERATOR_H_ */
