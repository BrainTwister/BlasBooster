// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_DYNAMICMATRIX_H_
#define BLASBOOSTER_CORE_DYNAMICMATRIX_H_

#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixBase.h"
#include "BlasBooster/Utilities/TypeName.h"
#include <memory>
#include <type_traits>

namespace BlasBooster {

typedef std::shared_ptr<MatrixBase> DynamicMatrix;
typedef std::shared_ptr<const MatrixBase> ConstDynamicMatrix;

template <> struct TypeName <DynamicMatrix>
{
    static const std::string value() { return "DynamicMatrix"; }
};

template <> struct TypeName <ConstDynamicMatrix>
{
    static const std::string value() { return "ConstDynamicMatrix"; }
};

} // namespace BlasBooster

namespace std {

template <>
struct is_arithmetic<BlasBooster::DynamicMatrix> : std::integral_constant<bool, false> {};

} // namespace std

#endif // BLASBOOSTER_CORE_DYNAMICMATRIX_H_
