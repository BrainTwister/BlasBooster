#ifndef BLOCKEDMATRIX_H_
#define BLOCKEDMATRIX_H_

#include "DenseMatrix.h"
#include "Parameter.h"

namespace BlasBooster {

typedef Parameter<size_t,ColumnMajor,nonfixed::Dimension<size_t>,
    NoLeadingDimension,nonfixed::UnblockedDimension<size_t> > BlockedDenseMatrixParameter;
typedef Matrix<Dense, DynamicMatrix, BlockedDenseMatrixParameter> BlockedDenseMatrix;
typedef Matrix<Dense, ConstDynamicMatrix, BlockedDenseMatrixParameter> ConstBlockedDenseMatrix;

template <class T, class P, size_t nbRows, size_t nbColumns>
struct FixedSizeBlockedDenseMatrix
{
    typedef typename P::IndexType IndexType;
    typedef typename P::orientation orientation;
    typedef Matrix<Dense, Matrix<Dense, T, Parameter<IndexType, orientation,
        fixed::Dimension<IndexType, nbRows, nbColumns> > > > type;
};

} // namespace BlasBooster

#endif /* BLOCKEDMATRIX_H_ */
