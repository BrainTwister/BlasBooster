// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_DYNAMICMATRIXTYPELIST_H_
#define BLASBOOSTER_CORE_DYNAMICMATRIXTYPELIST_H_

#include "BlasBooster/Utilities/TypeList.h"

namespace BlasBooster {

/// Forward declaration
template <class M, class T, class P>
struct Matrix;

/// Forward declaration
template <class T1, class T2>
struct MultipleMatrix;

/**
 * \brief Matrix types of the DynamicMatrix.
 *
 * A DynamicMatrix can only be converted into a matrix type listed here.
 * Other types will cause a runtime error.
 *
 * The order of the matrix type list is fixed by the important for the MatrixConverter.
 * The source matrix will be converted into the first matrix type which match the criteria.
 */
using DynamicMatrixTypeList = TypeList <
    Matrix<Sparse, float>,
    Matrix<Dense, float>,
    Matrix<Sparse, double>,
    MultipleMatrix<Matrix<Sparse, double>, Matrix<Sparse, float>>,
    MultipleMatrix<Matrix<Sparse, double>, Matrix<Dense, float>>,
    Matrix<Dense, double>
>;

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_DYNAMICMATRIXTYPELIST_H_