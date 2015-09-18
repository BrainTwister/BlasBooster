// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_GENERATETYPEMATRIX_H_
#define BLASBOOSTER_CORE_GENERATETYPEMATRIX_H_

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/TypeName.h"

namespace BlasBooster {

typedef Matrix<Dense,size_t> TypeMatrix;
typedef std::pair<size_t,size_t> Dimension;
typedef Matrix<Dense,Dimension> DimensionMatrix;
typedef Matrix<Dense,double> NormMatrix;

inline TypeMatrix generateTypeMatrix(BlockedDenseMatrix const& matrix)
{
    TypeMatrix typeMatrix(matrix.getNbRows(),matrix.getNbColumns());

    BlockedDenseMatrix::const_iterator blockMatrixCur(matrix.begin()), blockMatrixEnd(matrix.end());
    TypeMatrix::iterator typeMatrixCur(typeMatrix.begin()), typeMatrixEnd(typeMatrix.end());
    for ( ; blockMatrixCur != blockMatrixEnd; ++blockMatrixCur, ++typeMatrixCur )
    {
        *typeMatrixCur = (*blockMatrixCur)->getTypeIndex();
    }

    return typeMatrix;
}

inline DimensionMatrix generateDimensionMatrix(BlockedDenseMatrix const& matrix)
{
    DimensionMatrix dimMatrix(matrix.getNbRows(),matrix.getNbColumns());

    BlockedDenseMatrix::const_iterator blockMatrixCur(matrix.begin()), blockMatrixEnd(matrix.end());
    DimensionMatrix::iterator dimMatrixCur(dimMatrix.begin()), dimMatrixEnd(dimMatrix.end());
    for ( ; blockMatrixCur != blockMatrixEnd; ++blockMatrixCur, ++dimMatrixCur )
    {
        dimMatrixCur->first = getNbRows(*blockMatrixCur);
        dimMatrixCur->second = getNbColumns(*blockMatrixCur);
    }

    return dimMatrix;
}

template <> struct TypeName<Dimension>
{
    static const std::string value() { return "Dimension"; }
};

inline NormMatrix generateNormMatrix(BlockedDenseMatrix const& matrix)
{
    NormMatrix normMatrix(matrix.getNbRows(),matrix.getNbColumns());

    BlockedDenseMatrix::const_iterator blockMatrixCur(matrix.begin()), blockMatrixEnd(matrix.end());
    NormMatrix::iterator normMatrixCur(normMatrix.begin()), normMatrixEnd(normMatrix.end());
    for ( ; blockMatrixCur != blockMatrixEnd; ++blockMatrixCur, ++normMatrixCur )
    {
        *normMatrixCur = getNorm(*blockMatrixCur);
    }

    return normMatrix;
}

inline std::ostream& operator << (std::ostream& os, Dimension const& dimension)
{
    return os << dimension.first << "x" << dimension.second;
}

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_GENERATETYPEMATRIX_H_
