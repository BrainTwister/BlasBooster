#include "BlasBooster/MatrixFactory/MatrixFileImporter.h"
#include <fstream>

using namespace std;

namespace BlasBooster {

Matrix<Dense,double> MatrixFileImporter::getMatrix() const
{
	Matrix<Dense,double> matrix(nbRows,nbColumns);

	ifstream is(file.c_str(), ifstream::binary);
	is.read((char*)matrix.getDataPointer(), nbRows * nbColumns * sizeof(double));

    return matrix;
}

} // namespace BlasBooster

