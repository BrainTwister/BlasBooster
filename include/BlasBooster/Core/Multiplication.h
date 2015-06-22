// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MULTIPLICATION_H_
#define MULTIPLICATION_H_

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/Cursor.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixFiller.h"
#include "BlasBooster/Core/TypeList.h"
#include "BlasBooster/Utilities/exec_if_2dim.h"
#include "BlasBooster/Utilities/TypeChecker.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <boost/lexical_cast.hpp>
#include <boost/mpl/and.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace BlasBooster {

/// Primary template matrix multiplication must never be instantiated.
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3>
struct MultiplicationFunctor
{
    void operator () (Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B, Matrix<M3,T3,P3>& C)
    {
        static_assert(wrong_t<M1>::value, "Primary template must not be instantiated.");
    }
};

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
struct MultiplicationFunctor<Dense,T1,P1,Dense,T2,P2,Dense,T3,P3>
 : public GeneralDenseMultiplicationFunctor<T1,P1,T2,P2,T3,P3>
{};

#if 0
/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via extern BLAS dgemm
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(),B.getNbColumns());

        char transA = 'N';
        char transB = 'N';
        double alpha = 1.0;
        double beta = 0.0;
        int M = A.getNbRows();
        int N = B.getNbColumns();
        int K = A.getNbColumns();
        int LDA = A.getNbRows();
        int LDB = A.getNbColumns();
        int LDC = A.getNbRows();

        double *pA = const_cast<double*>(A.getDataPointer());
        double *pB = const_cast<double*>(B.getDataPointer());
        double *pC = C.getDataPointer();

        IntelMKL::dgemm(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,float> via extern BLAS sgemm
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,float,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(),B.getNbColumns());

        char transA = 'N';
        char transB = 'N';
        float alpha = 1.0f;
        float beta = 0.0f;
        int M = A.getNbRows();
        int N = B.getNbColumns();
        int K = A.getNbColumns();
        int LDA = A.getNbRows();
        int LDB = A.getNbColumns();
        int LDC = A.getNbRows();

        float *pA = const_cast<float*>(A.getDataPointer());
        float *pB = const_cast<float*>(B.getDataPointer());
        float *pC = C.getDataPointer();

        IntelMKL::sgemm(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};
#endif

/// Matrix multiplication specialized for DynamicMatrix Dense, Dense.
template <class P1, class P2, class P3>
struct MultiplicationFunctor<Dense,DynamicMatrix,P1,Dense,DynamicMatrix,P2,Dense,DynamicMatrix,P3>
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
                    *curColumnC += (*curColumnA) * (*curRowB);
                }

                //TODO: ConvertToTheBest
            }
        }
    }
};

template <class T1, class P1,
           class T2, class P2,
           class T3, class P3>
struct MultiplicationFunctor<Sparse,T1,P1,Sparse,T2,P2,Sparse,T3,P3>
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

template <class T1, class P1,
           class T2, class P2,
           class T3, class P3>
struct MultiplicationFunctor<Sparse,T1,P1,Dense,T2,P2,Dense,T3,P3>
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

template <class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct MultiplicationFunctor<Dense,T1,P1,Sparse,T2,P2,Dense,T3,P3>
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
struct MultiplicationFunctor<M1,T1,P1,M2,T2,P2,typename boost::enable_if<
    boost::mpl::or_<boost::is_same<M1,Zero>,boost::is_same<M2,Zero> > >::type,T3,P3>
{
    void operator () (Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B, Matrix<Zero,T3,P3>& C)
    {
        C.resize(A.getNbRows(),B.getNbColumns());
    }
};

/// Dummy operator to define resulting matrix type by multiplication by using decltype
Dense operator * (Dense, Dense);
Dense operator * (Dense, Sparse);
Dense operator * (Sparse, Dense);
Sparse operator * (Sparse, Sparse);
Zero operator * (Dense, Zero);
Zero operator * (Zero, Dense);
Zero operator * (Sparse, Zero);
Zero operator * (Zero, Sparse);
Zero operator * (Zero, Zero);

/// Metafunction returning result type of matrix-matrix multiplication
template <class M1, class T1,
          class M2, class T2, class P>
struct MultiplicationResult
{
    typedef typename Matrix<
        typename boost::mpl::if_<
            boost::mpl::or_<
                boost::is_same<M1, Dense>,
                boost::is_same<M2, Dense>
            >,
            Dense,
            Sparse
        >::type,decltype(T1() * T2()),P
    >::type type;
};

/// Operator for Matrix multiplication
template <class M1, class T1,
          class M2, class T2, class P>
inline auto operator * (Matrix<M1,T1,P> const& A, Matrix<M2,T2,P> const& B)
    -> Matrix<decltype(M1() * M2()),decltype(T1() * T2()),P>
{
    Matrix<decltype(M1() * M2()),decltype(T1() * T2()),P> C;
    MultiplicationFunctor<M1,T1,P,M2,T2,P,decltype(M1() * M2()),decltype(T1() * T2()),P>()(A,B,C);
    return C;
}

/// Function for Matrix multiplication
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3>
inline void mult(Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B, Matrix<M3,T3,P3>& C)
{
    MultiplicationFunctor<M1,T1,P1,M2,T2,P2,M3,T3,P3>()(A,B,C);
}

/// Operator for MultipleMatrix multiplication
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator * (Matrix<M1,T1,P1> const& A, MultipleMatrix<X1,X2> const& B)
    -> decltype(Matrix<M1,T1,P1>() * X1() + Matrix<M1,T1,P1>() * X2())
{
    return A * B.getMatrix1() + A * B.getMatrix2();
}

/// Operator for MultipleMatrix multiplication
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator * (MultipleMatrix<X1,X2> const& A, Matrix<M1,T1,P1> const& B)
    -> decltype(X1() * Matrix<M1,T1,P1>() + X2() * Matrix<M1,T1,P1>())
{
    return A.getMatrix1() * B + A.getMatrix2() * B;
}

/// Operator for MultipleMatrix multiplication
template <class X1, class X2, class Y1, class Y2>
inline auto operator * (MultipleMatrix<X1,X2> const& A, MultipleMatrix<Y1,Y2> const& B)
    -> decltype(X1() * Y1() + X1() * Y2() + X2() * Y1() + X2() * Y2())
{
    return A.getMatrix1() * B.getMatrix1() + A.getMatrix1() * B.getMatrix2()
          + A.getMatrix2() * B.getMatrix1() + A.getMatrix2() * B.getMatrix2();
}

/// Functor for DynamicMatrix multiplication
struct DynamicMultFunctor
{
    typedef DynamicMatrix result_type;

    DynamicMultFunctor(DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) : ptrA_(ptrA), ptrB_(ptrB) {}

    template <class T1, class T2>
    result_type operator () (T1* = 0, T2* = 0) const
    {
        typedef decltype(*(boost::static_pointer_cast<T1>(ptrA_)) * *(boost::static_pointer_cast<T2>(ptrB_))) ResultType;

        DynamicMatrix ptrC(new ResultType);
        *(boost::static_pointer_cast<ResultType>(ptrC)) = *(boost::static_pointer_cast<T1>(ptrA_)) * *(boost::static_pointer_cast<T2>(ptrB_));

        return ptrC;
    }

    DynamicMatrix ptrA_;
    DynamicMatrix ptrB_;
};

/// Operator for DynamicMatrix multiplication
inline DynamicMatrix operator * (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
    return exec_if_2dim<TypeList>(TypeChecker(ptrA->getTypeIndex()),
        TypeChecker(ptrB->getTypeIndex()), DynamicMultFunctor(ptrA,ptrB));
}

} // namespace BlasBooster

#endif /* MULTIPLICATION_H_ */

