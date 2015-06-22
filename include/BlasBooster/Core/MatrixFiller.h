// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MATRIXFILLER_H_
#define MATRIXFILLER_H_

#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Utilities/wrong_t.h"

namespace BlasBooster {

struct NoFiller{};
struct ZeroFiller{};
struct FullFiller{};
struct ContinuousNumberFiller{};
struct HilbertFiller{};
struct DiagonalFiller{};

template <class FillerType, class M, class T, class P>
struct MatrixFillerFunctor
{
    void operator () (Matrix<M,T,P>& matrix)
    {
        static_assert(wrong_t<M>::value, "Primary template must not be instantiated.");
    }
};

template <class M, class T, class P>
struct MatrixFillerFunctor<NoFiller,M,T,P>
{
    void operator () (Matrix<M,T,P>& matrix) { /* do nothing */ }
};

template <class M, class T, class P>
struct MatrixFillerFunctor<ZeroFiller,M,T,P>
{
    void operator () (Matrix<M,T,P>& matrix)
    {
        for (typename Matrix<M,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur)
        {
            *iterCur = 0.0;
        }
    }
};

template <class M, class T, class P>
struct MatrixFillerFunctor<FullFiller,M,T,P>
{
    void operator () (Matrix<M,T,P>& matrix)
    {
        for (typename Matrix<M,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur)
        {
            *iterCur = 1.0;
        }
    }
};

template <class T, class P>
struct MatrixFillerFunctor<ContinuousNumberFiller,Dense,T,P>
{
    void operator () (Matrix<Dense,T,P>& matrix)
    {
        T value(1.0);
        for (typename Matrix<Dense,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur, value += 1.0)
        {
            *iterCur = value;
        }
    }
};

template <class T, class P>
struct MatrixFillerFunctor<ContinuousNumberFiller,Sparse,T,P>
{
    void operator () (Matrix<Sparse,T,P>& matrix)
    {
        T value(1.0);
        for (typename Matrix<Sparse,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur, value += 1.0)
        {
            *iterCur = value;
        }

        typename P::IndexType offset(0), key;
        typename Matrix<Sparse,T,P>::index_iterator iterKeyCur(matrix.beginKey());
        typename Matrix<Sparse,T,P>::index_iterator iterOffsetCur(matrix.beginOffset()), iterOffsetEnd(matrix.endOffset() - 1);
        for ( ; iterOffsetCur != iterOffsetEnd; ++iterOffsetCur, offset += matrix.getNbRows())
        {
            key = 0;
            while (key != matrix.getNbRows())
            {
                *iterKeyCur = key;
                ++iterKeyCur;
                ++key;
            }
            *iterOffsetCur = offset;
        }
        *iterOffsetCur = offset;
    }
};

template <class T, class P>
struct MatrixFillerFunctor<HilbertFiller,Dense,T,P>
{
    void operator () (Matrix<Dense,T,P>& matrix)
    {
        T one(1.0), row(1.0), column;

        typedef Cursor<Matrix<Dense,T,P>, Direction::Row> RowCursor;
        typedef Cursor<RowCursor, Direction::Column> ColumnCursor;
        for (RowCursor rowCur(matrix,0), rowEnd(matrix,matrix.getNbRows());
            rowCur != rowEnd; ++rowCur, row += one)
        {
            column = 1.0;
            for (ColumnCursor columnCur(matrix,rowCur.begin()), columnEnd(matrix,rowCur.end());
                columnCur != columnEnd; ++columnCur, column += one)
            {
                *columnCur = one / (row + column - one);
            }
        }
    }
};

template <class T, class P>
struct MatrixFillerFunctor<DiagonalFiller,Dense,T,P>
{
    void operator () (Matrix<Dense,T,P>& matrix)
    {
        if (matrix.getNbRows() != matrix.getNbColumns()) throw CoreException("DiagonalFiller: Matrix is not quadratic.");

//        typedef Cursor<Matrix<Dense,T,P>, Direction::Diagonal> DiagonalCursor;
//        for (DiagonalCursor cursorCur(matrix,0), cursorEnd(matrix,matrix.getNbRows());
//            cursorCur != cursorEnd; ++cursorCur)
//        {
//            // TODO: value
//            *cursorCur = 1.0;
//        }

        matrix = 0.0;

        for (size_t i(0); i != matrix.getNbRows(); ++i)
        {
            //matrix[i][i] = 1.0;
            matrix(i,i) = 1.0;
        }
    }
};

} // namespace BlasBooster

#endif /* MATRIXFILLER_H_ */
