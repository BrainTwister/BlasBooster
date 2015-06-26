#ifndef MATRIXFACTORY_H_
#define MATRIXFACTORY_H_

#include "BlasBooster/Core/DenseMatrix.h"

namespace BlasBooster {

struct MatrixFactory
{
	virtual Matrix<Dense,double> getMatrix() const = 0;

	virtual size_t getNbRows() const = 0;

	virtual size_t getNbColumns() const = 0;
};

typedef std::shared_ptr<MatrixFactory> PtrMatrixFactory;

} // namespace BlasBooster

#endif /* MATRIXFACTORY_H_ */
