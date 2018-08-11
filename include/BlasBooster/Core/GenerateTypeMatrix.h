#pragma once

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/TypeName.h"

namespace BlasBooster {

typedef Matrix<Dense, int> TypeMatrix;
typedef std::pair<size_t, size_t> Dim;
typedef Matrix<Dense, Dim> DimensionMatrix;
typedef Matrix<Dense, double> NormMatrix;

inline TypeMatrix generateTypeMatrix(BlockedDenseMatrix const& matrix)
{
    TypeMatrix typeMatrix(matrix.getNbRows(), matrix.getNbColumns());

    BlockedDenseMatrix::const_iterator blockMatrixCur(matrix.begin()), blockMatrixEnd(matrix.end());
    TypeMatrix::iterator typeMatrixCur(typeMatrix.begin()), typeMatrixEnd(typeMatrix.end());
    for ( ; blockMatrixCur != blockMatrixEnd; ++blockMatrixCur, ++typeMatrixCur )
    {
        *typeMatrixCur = (*blockMatrixCur)->getTypeIndex();
    }

    return typeMatrix;
}

inline std::array<size_t, GetSize<DynamicMatrixTypeList>::value> get_type_counting(BlockedDenseMatrix const& matrix)
{
    std::array<size_t, GetSize<DynamicMatrixTypeList>::value> type_counting;
    for (auto&& submatrix : matrix) ++type_counting[submatrix->getTypeIndex()];
    return type_counting;
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

template <>
struct TypeName<Dim>
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

inline std::ostream& operator << (std::ostream& os, Dim const& dimension)
{
    return os << dimension.first << "x" << dimension.second;
}

} // namespace BlasBooster
