#include "BlasBooster/MatrixFactory/MatrixFileImporter.h"
#include <fstream>

namespace BlasBooster {

Matrix<Dense,double> MatrixFileImporter::getMatrix() const
{
	Matrix<Dense,double> matrix(nbRows,nbColumns);

	std::ifstream is(file.c_str(), std::ifstream::binary);
	is.read((char*)matrix.getDataPointer(), nbRows * nbColumns * sizeof(double));

    return matrix;
}

} // namespace BlasBooster

