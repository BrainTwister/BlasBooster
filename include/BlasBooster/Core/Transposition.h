// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_TRANSPOSITION_H_
#define BLASBOOSTER_CORE_TRANSPOSITION_H_

#include "DenseMatrix.h"
#include "SparseMatrix.h"

namespace BlasBooster {

template <class T, class P>
Matrix<Dense,T,P> transpose(Matrix<Dense,T,P> const& matrix)
{
    Matrix<Dense,T,P> transposedMatrix(matrix.getNbColumns(),matrix.getNbRows());

    typedef Cursor< const Matrix<Dense,T,P>, Direction::Row > RowCursor;
    typedef Cursor< RowCursor, Direction::Column > ColumnCursor;

    typedef Cursor< Matrix<Dense,T,P>, Direction::Column > TransColumnCursor;
    typedef Cursor< TransColumnCursor, Direction::Row > TransRowCursor;

    RowCursor rowCur(matrix,0), rowEnd(matrix,matrix.getNbRows());
    TransColumnCursor transColumnCur(transposedMatrix,0);
    for ( ; rowCur != rowEnd; ++rowCur, ++transColumnCur)
    {
        ColumnCursor columnCur(matrix,rowCur.begin()), columnEnd(matrix,rowCur.end());
        TransRowCursor transRowCur(transposedMatrix,transColumnCur.begin());
        for ( ; columnCur != columnEnd; ++columnCur, ++transRowCur )
        {
            *transRowCur = *columnCur;
        }
    }

    return transposedMatrix;
}

template <class T, class P>
Matrix<Sparse,T,P> transpose(Matrix<Sparse,T,P> const& matrix)
{
    Matrix<Sparse,T,P> transposedMatrix(matrix.getNbColumns(), matrix.getNbRows(), matrix.nnz());

    typedef typename Matrix<Sparse,T,P>::IndexType IndexType;
    typedef typename Matrix<Sparse,T,P>::iterator iterator;
    typedef typename Matrix<Sparse,T,P>::index_iterator index_iterator;

    const iterator iterValueTransBeg(transposedMatrix.begin());
    const index_iterator iterKeyTransBeg(transposedMatrix.beginKey());
    const index_iterator iterOffsetTransBeg(transposedMatrix.beginOffset());
    const index_iterator iterOffsetTransBeg1(transposedMatrix.beginOffset() + 1);

    std::fill(transposedMatrix.beginOffset(), transposedMatrix.endOffset(), 0);

    // count number of elements in minor dimension
    for ( typename Matrix<Sparse,T,P>::const_index_iterator iterOffsetCur(matrix.beginOffset()),
        iterOffsetEnd(matrix.endOffset() - 1); iterOffsetCur != iterOffsetEnd; ++iterOffsetCur )
    {
        for ( typename Matrix<Sparse,T,P>::const_index_iterator iterKeyCur(matrix.beginKey() + *iterOffsetCur),
            iterKeyEnd(matrix.beginKey() + *(iterOffsetCur + 1)); iterKeyCur != iterKeyEnd; ++iterKeyCur )
        {
            ++iterOffsetTransBeg1[*iterKeyCur];
        }
    }

    // accumulate number of elements to new offsets of transposed matrix
    for ( typename Matrix<Sparse,T,P>::index_iterator iterOffsetTransCur(transposedMatrix.beginOffset() + 2),
        iterOffsetTransEnd(transposedMatrix.endOffset()); iterOffsetTransCur != iterOffsetTransEnd; ++iterOffsetTransCur )
    {
        *iterOffsetTransCur += *(iterOffsetTransCur - 1);
    }

    IndexType offset, key(0);
    std::vector<IndexType> currentOffset(transposedMatrix.sizeOffset() - 1);

    // insert values into new positions
    for ( typename Matrix<Sparse,T,P>::const_index_iterator iterOffsetCur(matrix.beginOffset()),
        iterOffsetEnd(matrix.endOffset() - 1); iterOffsetCur != iterOffsetEnd; ++iterOffsetCur, ++key )
    {
        typename Matrix<Sparse,T,P>::const_iterator iterValueCur(matrix.begin() + *iterOffsetCur);
        for ( typename Matrix<Sparse,T,P>::const_index_iterator iterKeyCur(matrix.beginKey() + *iterOffsetCur),
            iterKeyEnd(matrix.beginKey() + *(iterOffsetCur + 1)); iterKeyCur != iterKeyEnd; ++iterKeyCur, ++iterValueCur )
        {
            offset = iterOffsetTransBeg[*iterKeyCur] + currentOffset[*iterKeyCur];
            *(iterValueTransBeg + offset) = *iterValueCur;
            *(iterKeyTransBeg + offset) = key;
            ++currentOffset[*iterKeyCur];
        }
    }

    return transposedMatrix;
}

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_TRANSPOSITION_H_
