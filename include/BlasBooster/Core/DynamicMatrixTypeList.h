#pragma once

#include "BlasBooster/Core/EmptyTypes.h"
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
	Matrix<Zero>,
    Matrix<Sparse, float>,
    Matrix<Dense, float>,
    Matrix<Sparse, double>,
    MultipleMatrix<Matrix<Sparse, double>, Matrix<Sparse, float>>,
    MultipleMatrix<Matrix<Sparse, double>, Matrix<Dense, float>>,
    Matrix<Dense, double>
>;

} // namespace BlasBooster
