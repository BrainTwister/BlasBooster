#pragma once

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

} // namespace BlasBooster
