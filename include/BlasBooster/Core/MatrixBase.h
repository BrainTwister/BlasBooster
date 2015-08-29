// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MATRIXBASE_H_
#define BLASBOOSTER_CORE_MATRIXBASE_H_

#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/TypeName.h"
#include <cstddef>
#include <memory>
#include <type_traits>

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
    MultipleMatrix<Matrix<Sparse,double>, Matrix<Sparse,float>>,
    MultipleMatrix<Matrix<Sparse,double>, Matrix<Dense,float>>,
    Matrix<Dense, double>
>;

} // namespace BlasBooster

namespace std {

template <>
struct is_arithmetic<BlasBooster::DynamicMatrix> : std::integral_constant<bool, false> {};

} // namespace std

#endif // BLASBOOSTER_CORE_MATRIXBASE_H_
