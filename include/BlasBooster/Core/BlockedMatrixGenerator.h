// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_BLOCKEDMATRIXGENERATOR_H_
#define BLASBOOSTER_CORE_BLOCKEDMATRIXGENERATOR_H_

#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixConverter.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include <set>
#include <stdexcept>

namespace BlasBooster {

struct BlockedMatrixGenerator
{
    template <class T, class P>
    BlockedDenseMatrix operator () (Matrix<Dense,T,P> const& matrix, std::vector<size_t> const& rowBlockSizeList,
        std::vector<size_t> const& columnBlockSizeList, Threshold const& threshold) const
    {
        typedef Cursor<BlockedDenseMatrix, Direction::Row> RowCursor;
        typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
        typedef Parameter<typename P::IndexType, typename P::orientation, typename P::SizeType, LeadingDimension> ParameterType;
    
        BlockedDenseMatrix blockedMatrix(rowBlockSizeList.size(),columnBlockSizeList.size(),
            matrix.getNbRows(),matrix.getNbColumns());
    
        size_t subRowSize(0), subColumnSize(0);
        size_t subRowOffset(0), subColumnOffset(0);
    
        std::vector<size_t>::const_iterator iterRowBlockSizeList(rowBlockSizeList.begin());
        std::vector<size_t>::const_iterator iterColumnBlockSizeList(columnBlockSizeList.begin());
        for (RowCursor rowCur(blockedMatrix,0), rowEnd(blockedMatrix,blockedMatrix.getNbRows());
            rowCur != rowEnd; ++rowCur, ++iterRowBlockSizeList)
        {
            subRowSize = *iterRowBlockSizeList;
            subColumnOffset = 0;
            iterColumnBlockSizeList = columnBlockSizeList.begin();
            for (ColumnCursor columnCur(blockedMatrix,rowCur.begin()), columnEnd(blockedMatrix,rowCur.end());
                columnCur != columnEnd; ++columnCur, ++iterColumnBlockSizeList)
            {
                subColumnSize = *iterColumnBlockSizeList;
    
                Matrix<Dense,T,ParameterType> subMatrix(matrix,subRowSize,subColumnSize,subRowOffset,subColumnOffset);
    
                *columnCur = MatrixConverter()(subMatrix,threshold);
    
                subColumnOffset += subColumnSize;
            }
            subRowOffset +=subRowSize;
        }
        return blockedMatrix;
    }
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_BLOCKEDMATRIXGENERATOR_H_
