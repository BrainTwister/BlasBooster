#pragma once

#include "Matrix.h"
#include "NullType.h"
#include <string>

namespace BlasBooster {

template <class P>
class Matrix<Zero,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension
{
public: // typedefs

    typedef Matrix<Zero,P> self;
    typedef Zero matrix_type;
    typedef P parameter;
    typedef typename P::dimension dimension;
    typedef typename P::orientation orientation;
    typedef typename P::leadingDimension leadingDimension;
    typedef typename P::unblockedDimension unblockedDimension;
    typedef typename P::IndexType IndexType;

public: // member functions

    /// Default/Parameter constructor
    Matrix(IndexType nbRows = 0, IndexType nbColumns = 0);

    /// Default copy constructor
    Matrix(self const& other) = default;

    /// Conversion from other matrix
    template <class M2, class T2, class P2>
    Matrix(Matrix<M2,T2,P2> const& other);

    /// Default copy assignment constructor
    Matrix& operator = (self const& other) = default;

    /// Resize function for non-blocked matrix
    void resize(IndexType nbRows, IndexType nbColumns);

    size_t getNbRows() const { return dimension::nbRows_; }
    size_t getNbColumns() const { return dimension::nbColumns_; }

    const std::type_info& getTypeInfo() const { return typeid(*this); }

    size_t getTypeIndex() const { return typeIndex_; }

    static const size_t typeIndex_ = GetIndex<self, DynamicMatrixTypeList>::value;

    static const std::string name() { return "Matrix<Zero>"; }

};

/// Default/Parameter constructor
template <class P>
Matrix<Zero,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns)
 : dimension(nbRows,nbColumns)
{}

/// Conversion from other matrix
template <class P>
template <class M2, class T2, class P2>
Matrix<Zero,P>::Matrix(Matrix<M2,T2,P2> const& other)
 : dimension(other.getNbRows(), other.getNbColumns())
{}

/// Resize function for non-blocked matrix
template <class P>
void Matrix<Zero,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns)
{
    this->nbRows_ = nbRows;
    this->nbColumns_ = nbColumns;
}

} // namespace BlasBooster
