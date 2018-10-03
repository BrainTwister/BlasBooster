#pragma once

#include <type_traits>
#include <vector>

#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/Cursor.h"
#include "BlasBooster/Core/EmptyTypes.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/ZeroMatrix.h"
#include "BlasBooster/Utilities/Tracker.h"

namespace BlasBooster {

struct Native {};
struct TheBestPolicy;

/// Matrix multiplication specialized for Dense, Dense.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct GeneralDenseMultiplicationFunctor
{
    void operator () (Matrix<Dense,T1,P1> const& A, Matrix<Dense,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
       	[[maybe_unused]] Tracker<TrackerID::Native_GeneralDense> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns(), AllFiller<T3>(0.0));

        typename Matrix<Dense,T1,P1>::const_iterator iterA;
        typename Matrix<Dense,T2,P2>::const_iterator iterB(B.begin());
        typename Matrix<Dense,T3,P3>::iterator iterC;

        size_t nb_B_cols = B.getNbColumns();
        size_t nb_A_rows = A.getNbRows();
        size_t nb_B_rows = B.getNbRows();
        size_t nb_C_rows = C.getNbRows();
        for (size_t j = 0; j != nb_B_cols; ++j)
        {
            iterA = A.begin();
            for (size_t k = 0; k != nb_B_rows; ++k, ++iterB)
            {
                iterC = C.begin() + j * nb_C_rows;
                for (size_t i = 0; i != nb_A_rows; ++i, ++iterA, ++iterC)
                {
                    *iterC += (*iterA) * (*iterB);
                }
            }
        }
    }
};

/// Matrix multiplication specialized for Dense, Dense.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct GeneralDenseMultiplicationFunctorUsingCursor
{
    void operator () (Matrix<Dense,T1,P1> const& A, Matrix<Dense,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        typedef const Matrix<Dense,T1,P1> ConstMatrixA;
        typedef const Matrix<Dense,T2,P2> ConstMatrixB;
        typedef Matrix<Dense,T3,P3> MatrixC;

        typedef Cursor<ConstMatrixA, Direction::Row> RowCursorA;
        typedef Cursor<ConstMatrixB, Direction::Column> ColumnCursorB;
        typedef Cursor<MatrixC, Direction::Row> RowCursorC;

        typedef Cursor<RowCursorC, Direction::Column> ColumnCursorC;
        typedef Cursor<RowCursorA, Direction::Column> ColumnCursorA;
        typedef Cursor<ColumnCursorB, Direction::Row> RowCursorB;

        C.resize(A.getNbRows(),B.getNbColumns());

        RowCursorA curRowA(A,0), endRowA(A,A.getNbRows());
        RowCursorC curRowC(C,0);
        for ( ; curRowA != endRowA; ++curRowA, ++curRowC )
        {
            ColumnCursorB curColumnB(B,0), endColumnB(B,B.getNbColumns());
            ColumnCursorC curColumnC(C,curRowC.begin());
            for ( ; curColumnB != endColumnB; ++curColumnB, ++curColumnC )
            {
                ColumnCursorA curColumnA(A,curRowA.begin()), endColumnA(A,curRowA.end());
                RowCursorB curRowB(B,curColumnB.begin());

                *curColumnC = 0.0;

                for ( ; curColumnA != endColumnA; ++curColumnA, ++curRowB )
                {
                    *curColumnC += (*curColumnA) * (*curRowB);
                }
            }
        }
    }
};

/// Matrix multiplication specialized for Dense, Dense.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<Dense,T1,P1,Dense,T2,P2,Dense,T3,P3,Native>
 : public GeneralDenseMultiplicationFunctor<T1,P1,T2,P2,T3,P3>
{};

/// Matrix multiplication specialized for DynamicMatrix Dense, Dense.
template <class P1, class P2, class P3>
struct MultiplicationFunctor<Dense,DynamicMatrix,P1,Dense,DynamicMatrix,P2,Dense,DynamicMatrix,P3,Native>
{
    void operator () (Matrix<Dense,DynamicMatrix,P1> const& A, Matrix<Dense,DynamicMatrix,P2> const& B,
        Matrix<Dense,DynamicMatrix,P3>& C)
    {
        typedef const Matrix<Dense,DynamicMatrix,P1> ConstMatrixA;
        typedef const Matrix<Dense,DynamicMatrix,P2> ConstMatrixB;
        typedef Matrix<Dense,DynamicMatrix,P3> MatrixC;

        typedef Cursor<ConstMatrixA, Direction::Row> RowCursorA;
        typedef Cursor<ConstMatrixB, Direction::Column> ColumnCursorB;
        typedef Cursor<MatrixC, Direction::Row> RowCursorC;

        typedef Cursor<RowCursorC, Direction::Column> ColumnCursorC;
        typedef Cursor<RowCursorA, Direction::Column> ColumnCursorA;
        typedef Cursor<ColumnCursorB, Direction::Row> RowCursorB;

        C.resize(A.getNbRows(),B.getNbColumns(),A.getUnblockedRows(),B.getUnblockedColumns());

        RowCursorA curRowA(A,0), endRowA(A,A.getNbRows());
        RowCursorC curRowC(C,0);
        for ( ; curRowA != endRowA; ++curRowA, ++curRowC )
        {
            ColumnCursorB curColumnB(B,0), endColumnB(B,B.getNbColumns());
            ColumnCursorC curColumnC(C,curRowC.begin());
            for ( ; curColumnB != endColumnB; ++curColumnB, ++curColumnC )
            {
                ColumnCursorA curColumnA(A,curRowA.begin()), endColumnA(A,curRowA.end());
                RowCursorB curRowB(B,curColumnB.begin());

                if (curColumnA == endColumnA) continue;
                *curColumnC = ((*curColumnA) * (*curRowB)).template execute<TheBestPolicy>();
            	++curColumnA, ++curRowB;

                while (curColumnA != endColumnA)
                {
                    // TODO: Interface must be definable
                	*curColumnC = *curColumnC + ((*curColumnA) * (*curRowB)).template execute<TheBestPolicy>();
                	++curColumnA, ++curRowB;
                }
            }
        }
    }
};

/// Matrix multiplication specialized for Sparse * Sparse.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<Sparse,T1,P1,Sparse,T2,P2,Sparse,T3,P3,Native>
{
    void operator () (Matrix<Sparse,T1,P1> const& A, Matrix<Sparse,T2,P2> const& B, Matrix<Sparse,T3,P3>& C)
    {
       	[[maybe_unused]] Tracker<TrackerID::Native_sparse> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        typename Matrix<Sparse,T3,P3>::iterator iterValueCCur(C.begin());
        typename Matrix<Sparse,T3,P3>::index_iterator iterKeyCCur(C.beginKey());
        typename Matrix<Sparse,T3,P3>::index_iterator iterOffsetCCur(C.beginOffset());

        typename P3::IndexType key,offset(0);
        std::vector<T3> scr(A.getNbRows());

        for (typename Matrix<Sparse,T2,P2>::const_index_iterator iterOffsetBCur(B.beginOffset()),
            iterOffsetBEnd(B.endOffset() - 1); iterOffsetBCur != iterOffsetBEnd; ++iterOffsetBCur )
        {
            std::fill(scr.begin(),scr.end(),0.0);
            typename Matrix<Sparse,T2,P2>::const_iterator iterValueBCur(B.begin() + *iterOffsetBCur);
            for (typename Matrix<Sparse,T2,P2>::const_index_iterator iterKeyBCur(B.beginKey() + *iterOffsetBCur),
                iterKeyBEnd(B.beginKey() + *(iterOffsetBCur+1)); iterKeyBCur != iterKeyBEnd; ++iterKeyBCur, ++iterValueBCur)
            {
                typename Matrix<Sparse,T1,P1>::const_iterator iterValueACur(A.begin() + A.beginOffset()[*iterKeyBCur]);
                for (typename Matrix<Sparse,T1,P1>::const_index_iterator iterKeyACur(A.beginKey() + A.beginOffset()[*iterKeyBCur]),
                    iterKeyAEnd(A.beginKey() + A.beginOffset()[*(iterKeyBCur)+1]); iterKeyACur != iterKeyAEnd; ++iterKeyACur, ++iterValueACur )
                {
                    scr[*iterKeyACur] += *iterValueACur * *iterValueBCur;
                }
            }

            *iterOffsetCCur++ = offset;

            key = 0;
            for (typename std::vector<T3>::const_iterator iterCur(scr.begin()), iterEnd(scr.end());
                iterCur != iterEnd; ++iterCur, ++key )
            {
                if ( *iterCur ) {
                    *iterValueCCur++ = *iterCur;
                    *iterKeyCCur++ = key;
                    ++offset;
                }
            }
        }
        *iterOffsetCCur++ = offset;
    }
};

/// Matrix multiplication specialized for Sparse * Dense.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<Sparse,T1,P1,Dense,T2,P2,Dense,T3,P3,Native>
{
    void operator () (Matrix<Sparse,T1,P1> const& A, Matrix<Dense,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        typedef Cursor<const Matrix<Dense,T2,P2>, Direction::Column> ColumnCursorB;
        typedef Cursor<ColumnCursorB, Direction::Row> RowCursorB;
        typedef Cursor<Matrix<Dense,T3,P3>, Direction::Column> ColumnCursorC;
        typedef Cursor<ColumnCursorC, Direction::Row> RowCursorC;

       	[[maybe_unused]] Tracker<TrackerID::Native_sparse_dense> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns(), AllFiller<T3>(0.0));

        size_t col(0);
        for (typename Matrix<Sparse,T1,P1>::const_index_iterator iterOffsetACur(A.beginOffset()),
            iterOffsetAEnd(A.endOffset() - 1); iterOffsetACur != iterOffsetAEnd; ++iterOffsetACur, ++col)
        {
            typename Matrix<Sparse,T1,P1>::const_iterator iterValueACur(A.begin() + *iterOffsetACur);
            typename Matrix<Sparse,T1,P1>::const_index_iterator iterKeyACur(A.beginKey() + *iterOffsetACur), iterKeyAEnd(A.beginKey() + *(iterOffsetACur+1));
            for ( ; iterKeyACur != iterKeyAEnd; ++iterKeyACur, ++iterValueACur)
            {
                ColumnCursorB curColumnB(B,0), endColumnB(B,B.getNbColumns());
                ColumnCursorC curColumnC(C,0), endColumnC(C,C.getNbColumns());
                for ( ; curColumnB != endColumnB; ++curColumnB, ++curColumnC )
                {
                    RowCursorB curRowB(B,curColumnB.begin() + col);
                    RowCursorC curRowC(C,curColumnC.begin() + *iterKeyACur);

                    *curRowC += *iterValueACur * *curRowB;
                }
            }
        }
    }
};

/// Matrix multiplication specialized for Dense * Sparse.
template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<Dense,T1,P1,Sparse,T2,P2,Dense,T3,P3,Native>
{
    void operator () (Matrix<Dense,T1,P1> const& A, Matrix<Sparse,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        typedef Cursor<const Matrix<Dense,T1,P1>, Direction::Column> ColumnCursorA;
        typedef Cursor<ColumnCursorA, Direction::Row> RowCursorA;
        typedef Cursor<Matrix<Dense,T3,P3>, Direction::Column> ColumnCursorC;
        typedef Cursor<ColumnCursorC, Direction::Row> RowCursorC;

       	[[maybe_unused]] Tracker<TrackerID::Native_dense_sparse> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns(), AllFiller<T3>(0.0));

        size_t col(0);
        typename Matrix<Sparse,T2,P2>::const_index_iterator curOffsetB(B.beginOffset()),
            endOffsetB(B.endOffset()-1);
        for ( ; curOffsetB != endOffsetB; ++curOffsetB, ++col )
        {
            typename Matrix<Sparse,T2,P2>::const_iterator curValueB(B.begin() + *curOffsetB);
            typename Matrix<Sparse,T2,P2>::const_index_iterator curKeyB(B.beginKey() + *curOffsetB),
                        endKeyB(B.beginKey() + *(curOffsetB+1));
            ColumnCursorC curColumnC(C,col);
            for ( ; curKeyB != endKeyB; ++curKeyB, ++curValueB )
            {
                ColumnCursorA curColumnA(A,*curKeyB);
                RowCursorA curRowA(A,curColumnA.begin()), endRowA(A,curColumnA.end());
                RowCursorC curRowC(C,curColumnC.begin());
                for ( ; curRowA != endRowA; ++curRowA, ++curRowC )
                {
                    *curRowC += *curRowA * *curValueB;
                }
            }
        }
    }
};

/// Matrix multiplication specialized for Matrix<M,T,P> * Matrix<Zero,NullType,P>
template <class M, class T, class P>
struct MultiplicationFunctor<M,T,P,Zero,NullType,P,Zero,NullType,P,Native>
{
    void operator () (Matrix<M,T,P> const& A, Matrix<Zero,NullType,P> const& B, Matrix<Zero,NullType,P>& C) const
    {
       	[[maybe_unused]] Tracker<TrackerID::Native_matrix_zero> tracker;
    	assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());
    }
};

/// Matrix multiplication specialized for Matrix<Zero,NullType,P> * Matrix<M,T,P>
template <class M, class T, class P>
struct MultiplicationFunctor<Zero,NullType,P,M,T,P,Zero,NullType,P,Native>
{
    void operator () (Matrix<Zero,NullType,P> const& A, Matrix<M,T,P> const& B, Matrix<Zero,NullType,P>& C) const
    {
       	[[maybe_unused]] Tracker<TrackerID::Native_zero_matrix> tracker;
    	assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());
    }
};

/// Matrix multiplication specialized for Matrix<Zero,NullType,P> * Matrix<Zero,NullType,P>
template <class P>
struct MultiplicationFunctor<Zero,NullType,P,Zero,NullType,P,Zero,NullType,P,Native>
{
    void operator () (Matrix<Zero,NullType,P> const& A, Matrix<Zero,NullType,P> const& B, Matrix<Zero,NullType,P>& C) const
    {
       	[[maybe_unused]] Tracker<TrackerID::Native_zero_zero> tracker;
    	assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());
    }
};

} // namespace BlasBooster
