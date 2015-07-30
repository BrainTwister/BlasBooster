#ifndef MATRIXFACTORY_H_
#define MATRIXFACTORY_H_

#include "BlasBooster/Core/DenseMatrix.h"
#include <memory>

namespace BlasBooster {

struct MatrixFactory
{
	MatrixFactory(size_t nbRows = 0, size_t nbColumns = 0)
	 : nbRows(nbRows), nbColumns(nbColumns)
	{}

	virtual ~MatrixFactory() {}

	virtual Matrix<Dense,double> operator()() const = 0;

	virtual size_t getNbRows() const { return nbRows; }

	virtual size_t getNbColumns() const { return nbColumns; }

protected:

	size_t nbRows;

	size_t nbColumns;
};

typedef std::shared_ptr<MatrixFactory> PtrMatrixFactory;

} // namespace BlasBooster

#endif /* MATRIXFACTORY_H_ */
