// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MULTIPLICATION_NATIVE_H_
#define BLASBOOSTER_CORE_MULTIPLICATION_NATIVE_H_

#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/Cursor.h"
#include "BlasBooster/Core/Matrix.h"
//#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include <type_traits>
#include <vector>

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
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(),B.getNbColumns(),ZeroFiller());

        typename Matrix<Dense,T1,P1>::const_iterator iterA;
        typename Matrix<Dense,T2,P2>::const_iterator iterB(B.begin());
        typename Matrix<Dense,T3,P3>::iterator iterC;

        size_t i,j,k;
        for (j = 0; j != B.getNbColumns(); ++j)
        {
            iterA = A.begin();
            for (k = 0; k != B.getNbRows(); ++k, ++iterB)
            {
                iterC = C.begin() + j * C.getNbRows();
                for (i = 0; i != A.getNbRows(); ++i, ++iterA, ++iterC)
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

                *curColumnC = DynamicMatrix(new Matrix<Dense,double>(
                    getNbRows(*curColumnA),getNbColumns(*curRowB),ZeroFiller()));

                for ( ; curColumnA != endColumnA; ++curColumnA, ++curRowB )
                {
                    // TODO: Interface must be definable
                    *curColumnC += ((*curColumnA) * (*curRowB)).template execute<TheBestPolicy>();
                }

                //TODO: ConvertToTheBest

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
        C.resize(A.getNbRows(),B.getNbColumns());

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

        // Initialize result matrix
        C.resize(A.getNbRows(),B.getNbColumns(),ZeroFiller());

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

        // Initialize result matrix
        C.resize(A.getNbRows(),B.getNbColumns(),ZeroFiller());

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

/// Matrix multiplication specialized for Matrix<M1,T1,P1> * Matrix<M2,T2,P2> if M1 or M2 is Zero
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<M1,T1,P1,M2,T2,P2,typename std::enable_if<
    std::is_same<M1,Zero>{} or std::is_same<M2,Zero>{}, Zero>::type,T3,P3,Native>
{
    void operator () (Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B, Matrix<Zero,T3,P3>& C)
    {
        C.resize(A.getNbRows(),B.getNbColumns());
    }
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MULTIPLICATION_NATIVE_H_
