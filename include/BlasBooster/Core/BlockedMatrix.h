// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_BLOCKEDMATRIX_H_
#define BLASBOOSTER_CORE_BLOCKEDMATRIX_H_

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

#endif // BLASBOOSTER_CORE_BLOCKEDMATRIX_H_
