#ifndef GENERATETYPEMATRIX_H_
#define GENERATETYPEMATRIX_H_

#include "DenseMatrix.h"
#include "TypeName.h"

namespace BlasBooster {

typedef Matrix<Dense,size_t> TypeMatrix;
typedef std::pair<size_t,size_t> Dimension;
typedef Matrix<Dense,Dimension> DimensionMatrix;
typedef Matrix<Dense,double> NormMatrix;

TypeMatrix generateTypeMatrix(BlockedDenseMatrix const& matrix);

DimensionMatrix generateDimensionMatrix(BlockedDenseMatrix const& matrix);

template <> struct TypeName<Dimension>
{
	static const std::string value() { return "Dimension"; }
};

NormMatrix generateNormMatrix(BlockedDenseMatrix const& matrix);

std::ostream& operator << (std::ostream& stream, Dimension const& dimension);

} // namespace BlasBooster

#endif /* GENERATETYPEMATRIX_H_ */
