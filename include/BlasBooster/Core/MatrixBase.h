// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MATRIXBASE_H_
#define MATRIXBASE_H_

#include "BlasBooster/Utilities/TypeName.h"
#include <boost/operators.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits.hpp>
#include <cstddef>

/**
 * \brief Dense and sparse linear algebra operations.
 *
 * BlasBooster search the optimal way for linear algebra operations
 * by dividing the hole matrix in sub-blocks and decide at runtime which
 * algorithm is the optimal one in respect to accuracy and sparsity.
 */
namespace BlasBooster {

/**
 * \brief Abstract base class for all matrix types.
 *
 * Using dynamic polymorphism to decide matrix type at runtime.
 */
class MatrixBase
{
public:

    virtual ~MatrixBase() {}

    //virtual MatrixBase* clone() const = 0;

    virtual const std::type_info& getTypeInfo() const = 0;

    virtual size_t getTypeIndex() const = 0;

};

typedef boost::shared_ptr<MatrixBase> DynamicMatrix;
typedef boost::shared_ptr<const MatrixBase> ConstDynamicMatrix;

template <> struct TypeName<DynamicMatrix>
{
    static const std::string value() { return "DynamicMatrix"; }
};

template <> struct TypeName<ConstDynamicMatrix>
{
    static const std::string value() { return "ConstDynamicMatrix"; }
};

} // namespace BlasBooster

namespace boost {

template <>
struct is_arithmetic<BlasBooster::DynamicMatrix> : public false_type {};

} // namespace boost

#endif // MATRIXBASE_H_
