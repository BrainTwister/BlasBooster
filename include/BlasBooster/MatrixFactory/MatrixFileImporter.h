#ifndef MATRIXFILEIMPORTER_H_
#define MATRIXFILEIMPORTER_H_

#include "BlasBooster/MatrixFactory/MatrixFactory.h"
#include <string>

namespace BlasBooster {

/// Import a matrix from file
class MatrixFileImporter : public MatrixFactory
{
public:

	MatrixFileImporter(size_t nbRows, size_t nbColumns, std::string const& file)
     : nbRows(nbRows), nbColumns(nbColumns), file(file)
    {}

	virtual ~MatrixFileImporter() {}

	Matrix<Dense,double> getMatrix() const;

	size_t getNbRows() const { return nbRows; }
	size_t getNbColumns() const { return nbColumns; }

private:

	size_t nbRows;
	size_t nbColumns;

	std::string file;

};

} // namespace BlasBooster

#endif /* MATRIXFILEIMPORTER_H_ */
