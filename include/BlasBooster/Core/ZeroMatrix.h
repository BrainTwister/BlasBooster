#pragma once

#include "Matrix.h"
#include <string>

namespace BlasBooster {

template <class T, class P>
class Matrix<Zero,T,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension,
   public Storage<T,P::onStack,P::isFixed,P::dimension::size,P::isSubMatrix>,
   public NormPolicy<Matrix<Zero,T,P>, typename P::NormType>,
   public OccupationPolicy<Matrix<Zero,T,P>>
{
public: // typedefs

    typedef Matrix<Zero,T,P> self;
    typedef Zero matrix_type;
    typedef T value_type;
    typedef const T const_value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef P parameter;
    typedef typename P::dimension dimension;
    typedef typename P::orientation orientation;
    typedef typename P::leadingDimension leadingDimension;
    typedef typename P::unblockedDimension unblockedDimension;
    typedef typename P::IndexType IndexType;
    typedef Storage<T,P::onStack,P::isFixed,P::dimension::size,P::isSubMatrix> storage;
    typedef typename storage::iterator iterator;
    typedef typename storage::const_iterator const_iterator;

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

    const std::type_info& getTypeInfo() const { return typeid(*this); }

    size_t getTypeIndex() const { return typeIndex_; }

    static const size_t typeIndex_ = GetIndex<self, DynamicMatrixTypeList>::value;

    static const std::string name() { return "Matrix<Zero," + TypeName<T>::value() + ">"; }

};

/// Default/Parameter constructor
template <class T, class P>
Matrix<Zero,T,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns)
 : dimension(nbRows,nbColumns)
{}

/// Default copy constructor
template <class T, class P>
void Matrix<Zero,T,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns)
{
    this->nbRows_ = nbRows;
    this->nbColumns_ = nbColumns;
}

/// Conversion from other matrix
template <class T, class P>
template <class M2, class T2, class P2>
Matrix<Zero,T,P>::Matrix(Matrix<M2,T2,P2> const& other)
 : dimension(other.getNbRows(), other.getNbColumns())
{}

} // namespace BlasBooster
