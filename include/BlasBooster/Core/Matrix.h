// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MATRIX_H_
#define BLASBOOSTER_CORE_MATRIX_H_

#include "BlasBooster/Core/Parameter.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <cstddef>

namespace BlasBooster {

struct Dense{};
struct Sparse{};
struct Zero{};

/// Dummy type for Matrix<Zero,NoType,P>
struct NoType{};

/**
 * \brief Primary template for all matrix types.
 *
 * All matrix types are specialized from this template class.
 * M: MatrixType, e.g. Dense, Sparse
 * T: DataType, which can be a simple build-in type (double, float, int) or again a matrix
 * P: Parameters, which describes the inner structure of the matrix
 */
template <class M = Dense, class T = double, class P = Parameter<> >
struct Matrix
{
    static_assert(wrong_t<M>::value, "Matrix primary template must not be instantiated.");
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MATRIX_H_
