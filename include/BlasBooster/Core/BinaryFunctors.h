// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_BINARYFUNCTORS_H_
#define BLASBOOSTER_CORE_BINARYFUNCTORS_H_

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/DynamicMatrix.h"
#include "BlasBooster/Core/DynamicMatrixTypeList.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixBase.h"
#include "BlasBooster/Core/MultipleMatrix.h"
#include "BlasBooster/Utilities/exec_dyn_2dim.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace BlasBooster {

struct Plus {};
struct Minus {};

/// Binary operation functor
template <class Operation>
struct BinaryOperation
{
    template <class T1, class T2, class T3>
    void operator () (T1 const& a, T2 const& b, T3& c) const
    {
        static_assert(wrong_t<T1>::value, "Primary template must not be instantiated.");
    }
};

template <>
struct BinaryOperation<Plus>
{
    template <class T1, class T2, class T3>
    void operator () (T1 const& a, T2 const& b, T3& c) const
    {
        c = a + b;
    }
};

template <>
struct BinaryOperation<Minus>
{
    template <class T1, class T2, class T3>
    void operator () (T1 const& a, T2 const& b, T3& c) const
    {
        c = a - b;
    }
};

/// Unary operation functor
template <class Operation>
struct UnaryOperation
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        static_assert(wrong_t<T1>::value, "Primary template must not be instantiated.");
    }
};

/// Unary operation functor
template <>
struct UnaryOperation<Plus>
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        a = b;
    }
};

/// Unary operation functor
template <>
struct UnaryOperation<Minus>
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        a = -b;
    }
};

/// Operation assignment functor
template <class Operation>
struct OperationAssignment
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        static_assert(wrong_t<T1>::value, "Primary template must not be instantiated.");
    }
};

template <>
struct OperationAssignment<Plus>
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        a += b;
    }
};

template <>
struct OperationAssignment<Minus>
{
    template <class T1, class T2>
    void operator () (T1& a, T2 const& b) const
    {
        a -= b;
    }
};

/// Primary template must never be instantiated.
template <class Operation,
          class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3>
struct BinaryOperationFunctor
{
    void operator () (Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B, Matrix<M3,T3,P3>& C)
    {
        static_assert(wrong_t<M1>::value, "Primary template must not be instantiated.");
    }
};

/// Primary template must never be instantiated.
template <class Operation,
          class M1, class T1, class P1,
          class M2, class T2, class P2>
struct BinaryAssignmentOperationFunctor
{
    void operator () (Matrix<M1,T1,P1>& A, Matrix<M2,T2,P2> const& B)
    {
        static_assert(wrong_t<M1>::value, "Primary template must not be instantiated.");
    }
};

/// Template specialization for Dense, Dense.
template <class Operation,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,Dense,T1,P1,Dense,T2,P2,Dense,T3,P3>
{
    void operator () (Matrix<Dense,T1,P1> const& A, Matrix<Dense,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        typedef const Matrix<Dense,T1,P1> ConstMatrixA;
        typedef const Matrix<Dense,T2,P2> ConstMatrixB;
        typedef Matrix<Dense,T3,P3> MatrixC;

        typedef typename ConstMatrixA::const_iterator ConstIteratorA;
        typedef typename ConstMatrixB::const_iterator ConstIteratorB;
        typedef typename MatrixC::iterator IteratorC;

        if (A.getNbRows() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
        if (A.getNbColumns() != B.getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(),A.getNbColumns());

        ConstIteratorA curIterA(A.begin()), endIterA(A.end());
        ConstIteratorB curIterB(B.begin());
        IteratorC curIterC(C.begin());
        for ( ; curIterA != endIterA; ++curIterA, ++curIterB, ++curIterC)
        {
            BinaryOperation<Operation>()(*curIterA,*curIterB,*curIterC);
        }
    }
};

/// Template specialization for Matrix<Sparse,T1,P1> <Operation> Matrix<Sparse,T2,P2>.
template <class Operation,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,Sparse,T1,P1,Sparse,T2,P2,Sparse,T3,P3>
{
    void operator () (Matrix<Sparse,T1,P1> const& A, Matrix<Sparse,T2,P2> const& B, Matrix<Sparse,T3,P3>& C)
    {
        if (A.getNbRows() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
        if (A.getNbColumns() != B.getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        typename Matrix<Sparse,T1,P1>::const_iterator iterValueACur;
        typename Matrix<Sparse,T1,P1>::const_index_iterator iterKeyACur, iterKeyAEnd;
        typename Matrix<Sparse,T1,P1>::const_index_iterator iterOffsetACur(A.beginOffset()), iterOffsetAEnd(A.endOffset() - 1);

        typename Matrix<Sparse,T2,P2>::const_iterator iterValueBCur;
        typename Matrix<Sparse,T2,P2>::const_index_iterator iterKeyBCur, iterKeyBEnd;
        typename Matrix<Sparse,T2,P2>::const_index_iterator iterOffsetBCur(B.beginOffset());

        C.resize(A.getNbRows(),A.getNbColumns());

        typename Matrix<Sparse,T3,P3>::iterator iterValueCCur(C.begin());
        typename Matrix<Sparse,T3,P3>::index_iterator iterKeyCCur(C.beginKey());
        typename Matrix<Sparse,T3,P3>::index_iterator iterOffsetCCur(C.beginOffset());

        typename P3::IndexType offset(0);
        *iterOffsetCCur++ = offset;

        for ( ; iterOffsetACur != iterOffsetAEnd; ++iterOffsetACur, ++iterOffsetBCur, ++iterOffsetCCur)
        {
            iterValueACur = A.begin() + *iterOffsetACur;
            iterKeyACur = A.beginKey() + *iterOffsetACur;
            iterKeyAEnd = A.beginKey() + *(iterOffsetACur+1);
            iterValueBCur = B.begin() + *iterOffsetBCur;
            iterKeyBCur = B.beginKey() + *iterOffsetBCur;
            iterKeyBEnd = B.beginKey() + *(iterOffsetBCur+1);

            while (iterKeyACur != iterKeyAEnd and iterKeyBCur != iterKeyBEnd)
            {
                if (*iterKeyACur < *iterKeyBCur) {
                    *iterValueCCur = *iterValueACur;
                    *iterKeyCCur = *iterKeyACur;
                    ++iterValueACur; ++iterKeyACur;
                } else if (*iterKeyACur > *iterKeyBCur) {
                    UnaryOperation<Operation>()(*iterValueCCur,*iterValueBCur);
                    *iterKeyCCur = *iterKeyBCur;
                    ++iterValueBCur; ++iterKeyBCur;
                } else {
                    BinaryOperation<Operation>()(*iterValueACur,*iterValueBCur,*iterValueCCur);
                    *iterKeyCCur = *iterKeyACur;
                    ++iterValueACur; ++iterKeyACur; ++iterValueBCur; ++iterKeyBCur;
                }
                ++iterValueCCur; ++iterKeyCCur; ++offset;
            }

            while (iterKeyACur != iterKeyAEnd)
            {
                *iterValueCCur = *iterValueACur;
                *iterKeyCCur = *iterKeyACur;
                ++iterValueACur; ++iterKeyACur;
                ++iterValueCCur; ++iterKeyCCur; ++offset;
            }

            while (iterKeyBCur != iterKeyBEnd)
            {
                UnaryOperation<Operation>()(*iterValueCCur,*iterValueBCur);
                *iterKeyCCur = *iterKeyBCur;
                ++iterValueBCur; ++iterKeyBCur;
                ++iterValueCCur; ++iterKeyCCur; ++offset;
            }

            *iterOffsetCCur = offset;
        }
    }
};

/// Template specialization for Matrix<Dense,T1,P1> <Operation> Matrix<Sparse,T2,P2>.
template <class Operation,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,Dense,T1,P1,Sparse,T2,P2,Dense,T3,P3>
{
    void operator () (Matrix<Dense,T1,P1> const& A, Matrix<Sparse,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        if (A.getNbRows() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
        if (A.getNbColumns() != B.getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        typename Matrix<Sparse,T2,P2>::const_iterator iterValueBCur;
        typename Matrix<Sparse,T2,P2>::const_index_iterator iterKeyBCur, iterKeyBEnd;
        typename Matrix<Sparse,T2,P2>::const_index_iterator iterOffsetBCur(B.beginOffset()), iterOffsetBEnd(B.endOffset() - 1);

        C = A;

        typename Matrix<Dense,T3,P3>::iterator iterCCur(C.begin());

        for ( ; iterOffsetBCur != iterOffsetBEnd; ++iterOffsetBCur, iterCCur += C.getNbRows())
        {
            iterValueBCur = B.begin() + *iterOffsetBCur;
            iterKeyBCur = B.beginKey() + *iterOffsetBCur;
            iterKeyBEnd = B.beginKey() + *(iterOffsetBCur+1);

            for (; iterKeyBCur != iterKeyBEnd; ++iterKeyBCur, ++iterValueBCur)
            {
                OperationAssignment<Operation>()(*(iterCCur + *iterKeyBCur), *iterValueBCur);
            }
        }
    }
};

/// Template specialization for Matrix<Sparse,T1,P1> <Operation> Matrix<Dense,T2,P2>.
template <class Operation,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,Sparse,T1,P1,Dense,T2,P2,Dense,T3,P3>
{
    void operator () (Matrix<Sparse,T1,P1> const& A, Matrix<Dense,T2,P2> const& B, Matrix<Dense,T3,P3>& C)
    {
        // Because matrix addition is commutative it can be forwarded to C = B + A;
        BinaryOperationFunctor<Operation,Dense,T2,P2,Sparse,T1,P1,Dense,T3,P3>()(B,A,C);
    }
};

/// Template specialization for Matrix<M,T1,P1> <Operation> Matrix<Zero,T2,P2>.
template <class Operation, class M,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,M,T1,P1,Zero,T2,P2,M,T3,P3>
{
    void operator () (Matrix<M,T1,P1> const& A, Matrix<Zero,T2,P2> const& B, Matrix<M,T3,P3>& C)
    {
        // TODO: Operation
        C = A;
    }
};

/// Template specialization for Matrix<Zero,T1,P1> <Operation> Matrix<M,T2,P2>.
template <class Operation, class M,
          class T1, class P1,
          class T2, class P2,
          class T3, class P3>
struct BinaryOperationFunctor<Operation,Zero,T1,P1,M,T2,P2,M,T3,P3>
{
    void operator () (Matrix<Zero,T1,P1> const& A, Matrix<M,T2,P2> const& B, Matrix<M,T3,P3>& C)
    {
        // TODO: Operation
        C = B;
    }
};

/// Template specialization for Dense, Dense.
template <class Operation,
          class T1, class P1,
          class T2, class P2>
struct BinaryAssignmentOperationFunctor<Operation,Dense,T1,P1,Dense,T2,P2>
{
    void operator () (Matrix<Dense,T1,P1>& A, Matrix<Dense,T2,P2> const& B)
    {
        typedef Matrix<Dense,T1,P1> MatrixA;
        typedef const Matrix<Dense,T2,P2> ConstMatrixB;

        typedef typename MatrixA::iterator IteratorA;
        typedef typename ConstMatrixB::const_iterator ConstIteratorB;

        IteratorA curIterA(A.begin()), endIterA(A.end());
        ConstIteratorB curIterB(B.begin());
        for ( ; curIterA != endIterA; ++curIterA, ++curIterB)
        {
            OperationAssignment<Operation>()(*curIterA,*curIterB);
        }
    }
};

/// Template specialization for Sparse, Sparse.
template <class Operation,
          class T1, class P1,
          class T2, class P2>
struct BinaryAssignmentOperationFunctor<Operation,Sparse,T1,P1,Sparse,T2,P2>
{
    void operator () (Matrix<Sparse,T1,P1>& A, Matrix<Sparse,T2,P2> const& B)
    {
        throw std::runtime_error("4 not yet implemented.");
    }
};

/// Template specialization for Dense, Sparse.
template <class Operation,
          class T1, class P1,
          class T2, class P2>
struct BinaryAssignmentOperationFunctor<Operation,Dense,T1,P1,Sparse,T2,P2>
{
    void operator () (Matrix<Dense,T1,P1>& A, Matrix<Sparse,T2,P2> const& B)
    {
        if (A.getNbRows() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");
        if (A.getNbColumns() != B.getNbColumns()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        size_t col(0);
        for (typename Matrix<Sparse,T2,P2>::const_index_iterator iterOffsetCur(B.beginOffset()),
            iterOffsetEnd(B.endOffset()-1); iterOffsetCur != iterOffsetEnd; ++iterOffsetCur, ++col)
        {
            typename Matrix<Sparse,T2,P2>::const_iterator iterValueCur(B.begin() + *iterOffsetCur);
            typename Matrix<Sparse,T2,P2>::const_index_iterator iterKeyCur(B.beginKey() + *iterOffsetCur), iterKeyEnd(B.beginKey() + *(iterOffsetCur+1));
            for ( ; iterKeyCur != iterKeyEnd; ++iterKeyCur, ++iterValueCur)
            {
                OperationAssignment<Operation>()(A(*iterKeyCur,col),*iterValueCur);
            }
        }
    }
};

/// Template specialization for Sparse, Dense.
template <class Operation,
          class T1, class P1,
          class T2, class P2>
struct BinaryAssignmentOperationFunctor<Operation,Sparse,T1,P1,Dense,T2,P2>
{
    void operator () (Matrix<Sparse,T1,P1>& A, Matrix<Dense,T2,P2> const& B)
    {
        throw std::runtime_error("5 not yet implemented.");
    }
};

/// Template specialization for Matrix<M1,T1,P1> <Operation> Matrix<Zero,T2,P2>.
template <class Operation,
          class M1, class T1, class P1,
          class T2, class P2>
struct BinaryAssignmentOperationFunctor<Operation,M1,T1,P1,Zero,T2,P2>
{
    void operator () (Matrix<M1,T1,P1>& A, Matrix<Zero,T2,P2> const& B)
    {
        /* nothing to do */
    }
};

/// Dummy operator to define resulting matrix type by addition/subtraction used by decltype
Dense operator + (Dense, Dense);
Dense operator + (Dense, Sparse);
Dense operator + (Sparse, Dense);
Sparse operator + (Sparse, Sparse);
Dense operator - (Dense, Dense);
Dense operator - (Dense, Sparse);
Dense operator - (Sparse, Dense);
Sparse operator - (Sparse, Sparse);
Dense operator + (Dense, Zero);
Dense operator + (Zero, Dense);
Sparse operator + (Sparse, Zero);
Sparse operator + (Zero, Sparse);
Zero operator + (Zero, Zero);
Dense operator - (Dense, Zero);
Dense operator - (Zero, Dense);
Sparse operator - (Sparse, Zero);
Sparse operator - (Zero, Sparse);
Zero operator - (Zero, Zero);

template <class M1, class T1,
          class M2, class T2, class P>
inline auto operator + (Matrix<M1,T1,P> const& A, Matrix<M2,T2,P> const& B)
    -> Matrix<decltype(M1() + M2()),decltype(T1() + T2()),P>
{
    Matrix<decltype(M1() + M2()),decltype(T1() + T2()),P> C;
    BinaryOperationFunctor<Plus,M1,T1,P,M2,T2,P,
        decltype(M1() + M2()),decltype(T1() + T2()),P>()(A,B,C);
    return C;
}

template <class M1, class T1,
          class M2, class T2, class P>
inline Matrix<M1,T1,P>& operator += (Matrix<M1,T1,P>& A, Matrix<M2,T2,P> const& B)
{
    BinaryAssignmentOperationFunctor<Plus,M1,T1,P,M2,T2,P>()(A,B);
    return A;
}

template <class M1, class T1,
          class M2, class T2, class P>
inline auto operator - (Matrix<M1,T1,P> const& A, Matrix<M2,T2,P> const& B)
    -> Matrix<decltype(M1() - M2()),decltype(T1() - T2()),P>
{
    Matrix<decltype(M1() - M2()),decltype(T1() - T2()),P> C;
    BinaryOperationFunctor<Minus,M1,T1,P,M2,T2,P,
        decltype(M1() - M2()),decltype(T1() - T2()),P>()(A,B,C);
    return C;
}

template <class M1, class T1,
          class M2, class T2, class P>
inline Matrix<M1,T1,P>& operator -= (Matrix<M1,T1,P>& A, Matrix<M2,T2,P> const& B)
{
    BinaryAssignmentOperationFunctor<Minus,M1,T1,P,M2,T2,P>()(A,B);
    return A;
}

/// Operator for MultipleMatrix addition
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator + (Matrix<M1,T1,P1> const& A, MultipleMatrix<X1,X2> const& B)
    -> decltype(Matrix<M1,T1,P1>() + X1() + X2())
{
    return A + B.getMatrix1() + B.getMatrix2();
}

/// Operator for MultipleMatrix addition
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator + (MultipleMatrix<X1,X2> const& A, Matrix<M1,T1,P1> const& B)
    -> decltype(X1() + X2() + Matrix<M1,T1,P1>())
{
    return A.getMatrix1() + A.getMatrix2() + B;
}

/// Operator for MultipleMatrix addition
template <class X1, class X2, class Y1, class Y2>
inline auto operator + (MultipleMatrix<X1,X2> const& A, MultipleMatrix<Y1,Y2> const& B)
    -> decltype(X1() + X2() + Y1() + Y2())
{
    return A.getMatrix1() + A.getMatrix2() + B.getMatrix1() + B.getMatrix2();
}

/// Operator for MultipleMatrix addition assignment
template <class M1, class T1, class P1, class X1, class X2>
inline Matrix<M1,T1,P1>& operator += (Matrix<M1,T1,P1>& A, MultipleMatrix<X1,X2> const& B)
{
    return A += B.getMatrix1() + B.getMatrix2();
}

/// Operator for MultipleMatrix addition assignment
template <class M1, class T1, class P1, class X1, class X2>
inline MultipleMatrix<X1,X2>& operator += (MultipleMatrix<X1,X2>& A, Matrix<M1,T1,P1> const& B)
{
    A.getMatrix1() += B;
    A.getMatrix2() += B;
    return A;
}

/// Operator for MultipleMatrix addition assignment
template <class X1, class X2, class Y1, class Y2>
inline MultipleMatrix<X1,X2>& operator += (MultipleMatrix<X1,X2>& A, MultipleMatrix<Y1,Y2> const& B)
{
    A.getMatrix1() += B.getMatrix1();
    A.getMatrix2() += B.getMatrix1();
    A.getMatrix1() += B.getMatrix2();
    A.getMatrix2() += B.getMatrix2();
    return A;
}

/// Operator for MultipleMatrix subtraction
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator - (Matrix<M1,T1,P1> const& A, MultipleMatrix<X1,X2> const& B)
    -> decltype(Matrix<M1,T1,P1>() - X1() - X2())
{
    return A - B.getMatrix1() - B.getMatrix2();
}

/// Operator for MultipleMatrix subtraction
template <class M1, class T1, class P1, class X1, class X2>
inline auto operator - (MultipleMatrix<X1,X2> const& A, Matrix<M1,T1,P1> const& B)
    -> decltype(X1() + X2() - Matrix<M1,T1,P1>())
{
    return A.getMatrix1() + A.getMatrix2() - B;
}

/// Operator for MultipleMatrix subtraction
template <class X1, class X2, class Y1, class Y2>
inline auto operator - (MultipleMatrix<X1,X2> const& A, MultipleMatrix<Y1,Y2> const& B)
    -> decltype(X1() + X2() - Y1() + Y2())
{
    return A.getMatrix1() + A.getMatrix2() - B.getMatrix1() + B.getMatrix2();
}

/// Operator for MultipleMatrix addition assignment
template <class M1, class T1, class P1, class X1, class X2>
inline Matrix<M1,T1,P1>& operator -= (Matrix<M1,T1,P1>& A, MultipleMatrix<X1,X2> const& B)
{
    A -= B.getMatrix1();
    return A -= B.getMatrix2();
}

/// Operator for MultipleMatrix addition assignment
template <class M1, class T1, class P1, class X1, class X2>
inline MultipleMatrix<X1,X2>& operator -= (MultipleMatrix<X1,X2>& A, Matrix<M1,T1,P1> const& B)
{
    A.getMatrix1() -= B;
    A.getMatrix2() -= B;
    return A;
}

/// Operator for MultipleMatrix addition assignment
template <class X1, class X2, class Y1, class Y2>
inline MultipleMatrix<X1,X2>& operator -= (MultipleMatrix<X1,X2>& A, MultipleMatrix<Y1,Y2> const& B)
{
    A.getMatrix1() -= B.getMatrix1();
    A.getMatrix2() -= B.getMatrix1();
    A.getMatrix1() -= B.getMatrix2();
    A.getMatrix2() -= B.getMatrix2();
    return A;
}

/// Functor for DynamicMatrix addition
template <class T1, class T2>
struct DynamicAddFunctor
{
    DynamicMatrix operator () (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) const
    {
        typedef decltype(*(std::static_pointer_cast<T1>(ptrA)) + *(std::static_pointer_cast<T2>(ptrB))) ResultType;

        DynamicMatrix ptrC(new ResultType);
        *(std::static_pointer_cast<ResultType>(ptrC)) = *(std::static_pointer_cast<T1>(ptrA)) + *(std::static_pointer_cast<T2>(ptrB));

        return ptrC;
    }
};

/// Operator for DynamicMatrix addition
inline DynamicMatrix operator + (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
	return exec_dyn_2dim<DynamicMatrixTypeList, DynamicAddFunctor, TypeList<>,
	    std::function<DynamicMatrix(DynamicMatrix const&, DynamicMatrix const&)>>(ptrA, ptrB);
}

/// Functor for DynamicMatrix subtraction
template <class T1, class T2>
struct DynamicSubFunctor
{
    DynamicMatrix operator () (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) const
    {
        typedef decltype(*(std::static_pointer_cast<T1>(ptrA)) - *(std::static_pointer_cast<T2>(ptrB))) ResultType;

        DynamicMatrix ptrC(new ResultType);
        *(std::static_pointer_cast<ResultType>(ptrC)) = *(std::static_pointer_cast<T1>(ptrA)) - *(std::static_pointer_cast<T2>(ptrB));

        return ptrC;
    }
};

/// Operator for DynamicMatrix subtraction
inline DynamicMatrix operator - (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
	return exec_dyn_2dim<DynamicMatrixTypeList, DynamicSubFunctor, TypeList<>,
	    std::function<DynamicMatrix(DynamicMatrix const&, DynamicMatrix const&)>>(ptrA, ptrB);
}

/// Functor for DynamicMatrix addition assignment
template <class T1, class T2>
struct DynamicAddAssignFunctor
{
	DynamicMatrix operator () (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) const
    {
        *(std::static_pointer_cast<T1>(ptrA)) += *(std::static_pointer_cast<T2>(ptrB));
        return ptrA;
    }
};

/// Operator for DynamicMatrix addition assignment
inline DynamicMatrix operator += (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
	return exec_dyn_2dim<DynamicMatrixTypeList, DynamicAddAssignFunctor, TypeList<>,
	    std::function<DynamicMatrix(DynamicMatrix const&, DynamicMatrix const&)>>(ptrA, ptrB);
}

/// Functor for DynamicMatrix subtraction assignment
template <class T1, class T2>
struct DynamicSubAssignFunctor
{
	DynamicMatrix operator () (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) const
    {
        *(std::static_pointer_cast<T1>(ptrA)) -= *(std::static_pointer_cast<T2>(ptrB));
        return ptrA;
    }
};

/// Operator for DynamicMatrix subtraction assignment
inline DynamicMatrix operator -= (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
	return exec_dyn_2dim<DynamicMatrixTypeList, DynamicSubAssignFunctor, TypeList<>,
	    std::function<DynamicMatrix(DynamicMatrix const&, DynamicMatrix const&)>>(ptrA, ptrB);
}

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_BINARYFUNCTORS_H_
