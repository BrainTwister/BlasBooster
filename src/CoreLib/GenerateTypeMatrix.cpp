#include "BlockedMatrixGenerator.h"
#include "DynamicMatrixFunctions.h"
#include "GenerateTypeMatrix.h"

namespace BlasBooster {

TypeMatrix generateTypeMatrix(BlockedDenseMatrix const& matrix)
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

DimensionMatrix generateDimensionMatrix(BlockedDenseMatrix const& matrix)
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

NormMatrix generateNormMatrix(BlockedDenseMatrix const& matrix)
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

std::ostream& operator << (std::ostream& stream, Dimension const& dimension)
{
    return stream << dimension.first << "x" << dimension.second;
}

} // namespace BlasBooster
