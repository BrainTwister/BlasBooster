// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_ZEROMATRIX_H_
#define BLASBOOSTER_CORE_ZEROMATRIX_H_

#include "Matrix.h"

namespace BlasBooster {

template <class T, class P>
class Matrix<Zero,T,P>
 : public MatrixBase,
   public P::dimension,
   public P::leadingDimension,
   public P::unblockedDimension,
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

#endif // BLASBOOSTER_CORE_ZEROMATRIX_H_
