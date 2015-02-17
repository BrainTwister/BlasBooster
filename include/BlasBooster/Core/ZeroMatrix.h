#ifndef ZEROMATRIX_H_
#define ZEROMATRIX_H_

#include "Matrix.h"

namespace BlasBooster {

template <class T, class P>
class Matrix<Zero,T,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension,
   public NormPolicy<Matrix<Zero,T,P>, typename P::NormType>,
   public OccupationPolicy<Matrix<Zero,T,P> >,
   boost::equality_comparable<Matrix<Zero,T,P> >
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

public: // member functions

    /// Default/Parameter constructor
    Matrix(IndexType nbRows = 0, IndexType nbColumns = 0);

    /// Default copy constructor
    Matrix(self const& other) = default;

    /// Default copy assignment constructor
    Matrix& operator = (self const& other) = default;

    /// Resize function for non-blocked matrix
    void resize(IndexType nbRows, IndexType nbColumns);

};

template <class T, class P>
Matrix<Zero,T,P>::Matrix(typename P::IndexType nbRows, typename P::IndexType nbColumns)
 : dimension(nbRows,nbColumns)
{}

template <class T, class P>
void Matrix<Zero,T,P>::resize(typename P::IndexType nbRows, typename P::IndexType nbColumns)
{
	this->nbRows_ = nbRows;
	this->nbColumns_ = nbColumns;
}

} // namespace BlasBooster

#endif /* ZEROMATRIX_H_ */
