// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_PARAMETER_H_
#define BLASBOOSTER_CORE_PARAMETER_H_

#include "Dimension.h"
#include <complex>
#include <type_traits>

namespace BlasBooster {

class OnHeap{};
class OnStack{};

class NormOne{};
class NormTwo{};
class NormMax{};

template <
    class Index = size_t,
    class Orientation = ColumnMajor,
    class SizeArg = VariableSize,
    class LeadingDimension = NoLeadingDimension,
    class UnblockedDimension = NoUnblockedDimension,
    class Norm = NormTwo,
    class Storage = OnHeap
>
struct Parameter
{
    typedef Index IndexType;
    typedef Orientation orientation;
    typedef SizeArg SizeType;
    typedef Dimension<SizeArg, Orientation> dimension;
    typedef LeadingDimension leadingDimension;
    typedef UnblockedDimension unblockedDimension;
    typedef Norm NormType;
    static const bool isSubMatrix = !std::is_same<LeadingDimension, NoLeadingDimension>::value;
    static const bool isBlockedMatrix = !std::is_same<UnblockedDimension, NoUnblockedDimension>::value;
    static const bool onStack = std::is_same<Storage, OnStack>::value;
    static const bool isFixed = dimension::fixed;
};

} // namespace BlasBooster

namespace std {

template <typename T>
struct is_arithmetic<std::complex<T>> : public true_type {};

} // namespace std

#endif // BLASBOOSTER_CORE_PARAMETER_H_
