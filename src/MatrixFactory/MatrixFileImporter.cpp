#include "BlasBooster/MatrixFactory/MatrixFileImporter.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include <fstream>

namespace BlasBooster {

MatrixFileImporter::MatrixFileImporter(filesystem::path const& file)
 : MatrixFactory()
{
	std::ifstream is(file.c_str());
	if (!is)
		throw BlasBoosterException("Can't open file " + file.string());
    if (!(is >> nbRows >> nbColumns >> dataFile))
	    throw BlasBoosterException("Error reading file " + file.string());
}

Matrix<Dense,double> MatrixFileImporter::operator()() const
{
	Matrix<Dense,double> matrix(nbRows,nbColumns);

	std::ifstream is(dataFile.c_str(), std::ifstream::binary);
	if (!is)
		throw BlasBoosterException("Can't open file " + dataFile.string());
	if (!(is.read((char*)matrix.getDataPointer(), nbRows * nbColumns * sizeof(double))))
        throw BlasBoosterException("Error reading file " + dataFile.string());

    return matrix;
}

} // namespace BlasBooster

