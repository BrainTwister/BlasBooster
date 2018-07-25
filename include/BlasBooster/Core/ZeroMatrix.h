#pragma once

#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/NormPolicy.h"
#include "BlasBooster/Core/OccupationPolicy.h"
#include <string>

namespace BlasBooster {

template <class P>
class Matrix<Zero,NullType,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension,
   public NormPolicy<Matrix<Zero,NullType,P>, typename P::NormType>,
   public OccupationPolicy<Matrix<Zero,NullType,P>>
{
public: // typedefs

    typedef Matrix<Zero,NullType,P> self;
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

    bool operator == (self const& rhs) const {
        return dimension::operator==(rhs);
    }

    bool operator != (self const& rhs) const {
        return !operator==(rhs);
    }

    template <class P2>
    bool equal(Matrix<Zero,NullType,P2> const& rhs) const {
        return operator==(rhs);
    }

    template <class P2>
    bool notEqual(Matrix<Zero,NullType,P2> const& rhs) const {
        return !equal(rhs);
    }

    size_t getNbRows() const { return dimension::nbRows_; }
    size_t getNbColumns() const { return dimension::nbColumns_; }

    const std::type_info& getTypeInfo() const { return typeid(*this); }

    size_t getTypeIndex() const { return typeIndex_; }

    static const size_t typeIndex_ = GetIndex<self, DynamicMatrixTypeList>::value;

    static const std::string name() { return "Matrix<Zero>"; }

private:

    template <class M2, class T2, class P2>
    friend struct Matrix;

};

/// Default/Parameter constructor
template <class P>
Matrix<Zero,NullType,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns)
 : dimension(nbRows,nbColumns)
{}

/// Conversion from other matrix
template <class P>
template <class M2, class T2, class P2>
Matrix<Zero,NullType,P>::Matrix(Matrix<M2,T2,P2> const& other)
 : dimension(other.getNbRows(), other.getNbColumns())
{}

/// Resize function for non-blocked matrix
template <class P>
void Matrix<Zero,NullType,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns)
{
    this->nbRows_ = nbRows;
    this->nbColumns_ = nbColumns;
}

template <class P, class NormType>
class NormPolicy<Matrix<Zero,NullType,P>,NormType>
{
public:

    double getNorm() const
    {
        return 0.0;
    }

    bool isNormLargerThan(double value) const
    {
        return 0.0 > value;
    }

    bool isNormSmallerThan(double value) const
    {
        return 0.0 < value;
    }
};

template <class P>
class OccupationPolicy<Matrix<Zero,NullType,P> >
{
public:

    size_t getNbOfSignificantElements(double threshold = 0.0) const
    {
        return 0;
    }

    double getOccupation(double threshold = 0.0) const
    {
        return 0.0;
    }

    bool isOccupationLargerThan(double value, double threshold = 0.0) const
    {
        return 0.0 > value;
    }

    bool isOccupationSmallerThan(double value, double threshold = 0.0) const
    {
        return 0.0 < value;
    }
};

} // namespace BlasBooster
