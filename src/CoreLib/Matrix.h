// Copyright (C) 2012-2014, Bernd Doser (bernd.doser@gmx.de)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MATRIX_H_
#define MATRIX_H_

#include "MatrixBase.h"
#include "Parameter.h"
#include "BoostLib/wrong_t.h"
#include <boost/operators.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits.hpp>
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
 */
template <class M = Dense, class T = double, class P = Parameter<> >
struct Matrix
{
    static_assert(wrong_t<M>::value, "Matrix primary template must not be instantiated.");
};

} // namespace BlasBooster

#endif // MATRIX_H_
