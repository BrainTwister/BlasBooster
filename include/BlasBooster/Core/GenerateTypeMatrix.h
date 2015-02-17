// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef GENERATETYPEMATRIX_H_
#define GENERATETYPEMATRIX_H_

#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Utilities/TypeName.h"

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
