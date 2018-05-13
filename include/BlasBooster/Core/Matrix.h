#pragma once

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
template <class M = Dense, class T = double, class P = Parameter<>>
struct Matrix
{
    static_assert(wrong_t<M>::value, "Matrix primary template must not be instantiated.");
};

} // namespace BlasBooster
