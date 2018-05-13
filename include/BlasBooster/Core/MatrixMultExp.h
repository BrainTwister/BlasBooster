#pragma once

#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/DynamicMatrix.h"
#include "BlasBooster/Core/DynamicMatrixTypeList.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MatrixFiller.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Utilities/exec_dyn_2dim.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace BlasBooster {

/// Primary expression template for matrix-matrix multiplication must never be instantiated.
template <class TypeA, class TypeB>
struct MatrixMultExp
{
    static_assert(wrong_t<TypeA>::value, "Primary template must not be instantiated.");
};

/// Expression template for multiplication Matrix * Matrix
template <class M1, class T1, class P1, class M2, class T2, class P2>
class MatrixMultExp<Matrix<M1,T1,P1>, Matrix<M2,T2,P2>>
{
public:

    MatrixMultExp(Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    auto execute() const -> Matrix<decltype(M1() * M2()), decltype(T1() * T2()), decltype(P1() * P2())>
    {
        Matrix<decltype(M1() * M2()), decltype(T1() * T2()), decltype(P1() * P2())> C;
        MultiplicationFunctor<M1,T1,P1,M2,T2,P2, decltype(M1() * M2()), decltype(T1() * T2()), decltype(P1() * P2()), Interface>()(A,B,C);
        return C;
    }

private:

    Matrix<M1,T1,P1> const& A;
    Matrix<M2,T2,P2> const& B;

};

/// Expression template for multiplication Matrix<Dense,DynamicMatrix> * Matrix<Dense,DynamicMatrix>
template <class M1, class M2, class P>
class MatrixMultExp< Matrix<M1,DynamicMatrix,P>, Matrix<M2,DynamicMatrix,P> >
{
public:

    MatrixMultExp(Matrix<M1,DynamicMatrix,P> const& A, Matrix<M2,DynamicMatrix,P> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    auto execute() const -> Matrix<decltype(M1() * M2()), DynamicMatrix, P>
    {
        Matrix<decltype(M1() * M2()), DynamicMatrix, P> C;
        MultiplicationFunctor<M1,DynamicMatrix,P,M2,DynamicMatrix,P, decltype(M1() * M2()), DynamicMatrix, P, Interface>()(A,B,C);
        return C;
    }

private:

    Matrix<M1,DynamicMatrix,P> const& A;
    Matrix<M2,DynamicMatrix,P> const& B;

};

/// Expression template for multiplication Matrix * MultipleMatrix.
template <class M1, class T1, class P1, class X1, class X2>
class MatrixMultExp< Matrix<M1,T1,P1>, MultipleMatrix<X1,X2> >
{
public:

    MatrixMultExp(Matrix<M1,T1,P1> const& A, MultipleMatrix<X1,X2> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    auto execute() const -> decltype((Matrix<M1,T1,P1>() * X1()).template execute<Interface>() + (Matrix<M1,T1,P1>() * X2()).template execute<Interface>())
    {
        return (A * B.getMatrix1()).template execute<Interface>() + (A * B.getMatrix2()).template execute<Interface>();
    }

private:

    Matrix<M1,T1,P1> const& A;
    MultipleMatrix<X1,X2> const& B;

};

/// Expression template for multiplication MultipleMatrix * Matrix.
template <class M1, class T1, class P1, class X1, class X2>
class MatrixMultExp< MultipleMatrix<X1,X2>, Matrix<M1,T1,P1> >
{
public:

    MatrixMultExp(MultipleMatrix<X1,X2> const& A, Matrix<M1,T1,P1> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    auto execute() const -> decltype((X1() * Matrix<M1,T1,P1>()).template execute<Interface>() + (X2() * Matrix<M1,T1,P1>()).template execute<Interface>())
    {
        return (A.getMatrix1() * B).template execute<Interface>() + (A.getMatrix2() * B).template execute<Interface>();
    }

private:

    MultipleMatrix<X1,X2> const& A;
    Matrix<M1,T1,P1> const& B;

};

/// Expression template for multiplication MultipleMatrix * MultipleMatrix.
template <class X1, class X2, class Y1, class Y2>
class MatrixMultExp< MultipleMatrix<X1,X2>, MultipleMatrix<Y1,Y2> >
{
public:

    MatrixMultExp(MultipleMatrix<X1,X2> const& A, MultipleMatrix<Y1,Y2> const& B)
     : A(A), B(B)
    {}

    template <class Interface>
    auto execute() const -> decltype((X1() * Y1()).template execute<Interface>() + (X1() * Y2()).template execute<Interface>() +
        (X2() * Y1()).template execute<Interface>() + (X2() * Y2()).template execute<Interface>())
    {
        return (A.getMatrix1() * B.getMatrix1()).template execute<Interface>() + (A.getMatrix1() * B.getMatrix2()).template execute<Interface>() +
            (A.getMatrix2() * B.getMatrix1()).template execute<Interface>() + (A.getMatrix2() * B.getMatrix2()).template execute<Interface>();
    }

private:

    MultipleMatrix<X1,X2> const& A;
    MultipleMatrix<Y1,Y2> const& B;

};

/// Functor for multiplication DynamicMatrix * DynamicMatrix
template <class Interface, class T1, class T2>
struct DynamicMultFunctor
{
	DynamicMatrix operator () (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB) const
    {
        typedef decltype((T1() * T2()).template execute<Interface>()) ResultType;

        DynamicMatrix ptrC(new ResultType);
        *(std::static_pointer_cast<ResultType>(ptrC)) = (*(std::static_pointer_cast<T1>(ptrA)) * *(std::static_pointer_cast<T2>(ptrB))).template execute<Interface>();

        return ptrC;
    }
};

/// Expression template for multiplication DynamicMatrix * DynamicMatrix.
template <>
class MatrixMultExp<DynamicMatrix, DynamicMatrix>
{
public:

    MatrixMultExp(DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
     : ptrA(ptrA), ptrB(ptrB)
    {}

    template <class Interface>
    DynamicMatrix execute() const
    {
        return exec_dyn_2dim<DynamicMatrixTypeList, DynamicMultFunctor, TypeList<Interface>,
        	std::function<DynamicMatrix(DynamicMatrix const&, DynamicMatrix const&)>>(ptrA, ptrB);
    }

private:

    DynamicMatrix const& ptrA;
    DynamicMatrix const& ptrB;

};

/// Operator for multiplication Matrix * Matrix
template <class M1, class T1, class P1, class M2, class T2, class P2>
inline MatrixMultExp< Matrix<M1,T1,P1>, Matrix<M2,T2,P2> > operator * (Matrix<M1,T1,P1> const& A, Matrix<M2,T2,P2> const& B)
{
    return MatrixMultExp< Matrix<M1,T1,P1>, Matrix<M2,T2,P2> >(A,B);
}

/// Operator for multiplication Matrix * MultipleMatrix.
template <class M1, class T1, class P1, class X1, class X2>
inline MatrixMultExp< Matrix<M1,T1,P1>, MultipleMatrix<X1,X2> > operator * (Matrix<M1,T1,P1> const& A, MultipleMatrix<X1,X2> const& B)
{
    return MatrixMultExp< Matrix<M1,T1,P1>, MultipleMatrix<X1,X2> >(A,B);
}

/// Operator for multiplication MultipleMatrix * Matrix.
template <class M1, class T1, class P1, class X1, class X2>
inline MatrixMultExp< MultipleMatrix<X1,X2>, Matrix<M1,T1,P1> > operator * (MultipleMatrix<X1,X2> const& A, Matrix<M1,T1,P1> const& B)
{
    return MatrixMultExp< MultipleMatrix<X1,X2>, Matrix<M1,T1,P1> >(A,B);
}

/// Operator for multiplication MultipleMatrix * MultipleMatrix.
template <class X1, class X2, class Y1, class Y2>
inline MatrixMultExp< MultipleMatrix<X1,X2>, MultipleMatrix<Y1,Y2> > operator * (MultipleMatrix<X1,X2> const& A, MultipleMatrix<Y1,Y2> const& B)
{
    return MatrixMultExp< MultipleMatrix<X1,X2>, MultipleMatrix<Y1,Y2> >(A,B);
}

/// Operator for multiplication DynamicMatrix * DynamicMatrix
inline MatrixMultExp<DynamicMatrix, DynamicMatrix> operator * (DynamicMatrix const& ptrA, DynamicMatrix const& ptrB)
{
    return MatrixMultExp<DynamicMatrix, DynamicMatrix>(ptrA,ptrB);
}

} // namespace BlasBooster
