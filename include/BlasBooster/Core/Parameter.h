// Copyright (C) 2012-2014, Bernd Doser (bernd.doser@gmx.de)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "Dimension.h"
#include <boost/mpl/not.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>

namespace BlasBooster {

class RowMajor{};
class ColumnMajor{};

class OnHeap{};
class OnStack{};

class NormOne{};
class NormTwo{};
class NormMax{};

template <
    class Index = size_t,
    class Orientation = ColumnMajor,
    class Dimension = nonfixed::Dimension<Index>,
    class LeadingDimension = NoLeadingDimension,
    class UnblockedDimension = NoUnblockedDimension,
    class Norm = NormTwo,
    class Storage = OnHeap
>
struct Parameter
{
    typedef Index IndexType;
    typedef Orientation orientation;
    typedef Dimension dimension;
    typedef LeadingDimension leadingDimension;
    typedef UnblockedDimension unblockedDimension;
    typedef Norm NormType;
    static const bool isSubMatrix = boost::mpl::not_<boost::is_same<LeadingDimension,NoLeadingDimension> >::value;
    static const bool isBlockedMatrix = boost::mpl::not_<boost::is_same<UnblockedDimension,NoUnblockedDimension> >::value;
    static const bool onStack = boost::is_same<Storage,OnStack>::value;
    static const bool isFixed = Dimension::fixed;
};

} // namespace BlasBooster

namespace boost {

template < typename T >
struct is_arithmetic< std::complex<T> > : public true_type {};

} // namespace boost

#endif /* PARAMETER_H_ */
