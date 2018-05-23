#pragma once

#include "BlasBooster/Core/Matrix.h"

namespace BlasBooster {

struct NoFiller
{
	template <class M, class T, class P>
    void operator () (Matrix<M,T,P>&) const
    {}
};

template <class T2>
struct AllFiller
{
	AllFiller(T2 value) : value(value) {}

	template <class M, class T, class P>
    void operator () (Matrix<M,T,P>& matrix) const
    {
        // TODO: Use range-based for loop
        for (typename Matrix<M,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur)
        {
            *iterCur = value;
        }
    }

    T2 value;
};

struct ContinuousNumberFiller
{
	template <class T, class P>
    void operator () (Matrix<Dense,T,P>& matrix) const
    {
        T value(1.0);
        for (typename Matrix<Dense,T,P>::iterator iterCur(matrix.begin()), iterEnd(matrix.end());
            iterCur != iterEnd; ++iterCur, value += 1.0)
        {
            *iterCur = value;
        }
    }

	template <class T, class P>
    void operator () (Matrix<Sparse,T,P>& matrix) const
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

struct HilbertFiller
{
	template <class T, class P>
    void operator () (Matrix<Dense,T,P>& matrix) const
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

template <class T2>
struct DiagonalFiller
{
	DiagonalFiller(T2 value) : value(value) {}

	template <class T, class P>
    void operator () (Matrix<Dense,T,P>& matrix) const
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
            matrix(i,i) = value;
        }
    }

    T2 value;
};

} // namespace BlasBooster
