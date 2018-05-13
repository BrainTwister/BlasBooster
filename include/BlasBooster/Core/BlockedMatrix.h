#pragma once

#include "DenseMatrix.h"
#include "Parameter.h"

namespace BlasBooster {

/// Parameter type for BlockedDenseMatrix
typedef Parameter<
            size_t,
            ColumnMajor,
            VariableSize,
            NoLeadingDimension,
            UnblockedDimension
        > BlockedDenseMatrixParameter;

typedef Matrix<Dense, DynamicMatrix, BlockedDenseMatrixParameter> BlockedDenseMatrix;
typedef Matrix<Dense, ConstDynamicMatrix, BlockedDenseMatrixParameter> ConstBlockedDenseMatrix;

template <class T, class P, size_t nbRows, size_t nbColumns>
struct FixedSizeBlockedDenseMatrix
{
    typedef typename P::IndexType IndexType;
    typedef typename P::orientation orientation;
    typedef Matrix<Dense, Matrix<Dense, T, Parameter<IndexType, orientation, FixedSize<nbRows, nbColumns> > > > type;
};

} // namespace BlasBooster
