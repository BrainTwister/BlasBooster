#pragma once

#include "BlasBooster/Utilities/exec_dyn.h"
#include "BlasBooster/Utilities/TypeList.h"

namespace BlasBooster {

/// Primary template for NormFunctor
template <class NormType, class MatrixType>
struct NormFunctor
{
    double operator () (MatrixType const& A) const
    {
        static_assert(wrong_t<MatrixType>::value, "Primary template must not be instantiated.");
        return 0.0;
    }
};

/// Specialization for Matrix<Zero>
template <class P>
struct NormFunctor<NormTwo, Matrix<Zero,NullType,P>>
{
    double operator () (Matrix<Zero,NullType,P> const& m) const
    {
        return 0.0;
    }
};

/// norm function wrapper, forwarded to the NormFunctor for partial specialization
template <class NormType, class MatrixType>
inline double norm(MatrixType const& m)
{
    return NormFunctor<NormType, MatrixType>()(m);
}

template <class M, class T, class P>
struct NormFunctor<NormOne, Matrix<M,T,P> >
{
    double operator () (Matrix<M,T,P> const& m) const
    {
        typedef const Matrix<M,T,P> MatrixType;

        double sum(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            sum += std::abs(*iterCur);
        }
        return sum;
    }
};

template <class M, class P>
struct NormFunctor<NormOne,Matrix<M,DynamicMatrix,P> >
{
    double operator () (Matrix<M,DynamicMatrix,P> const& m) const
    {
        typedef const Matrix<M,DynamicMatrix,P> MatrixType;

        double sum(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            sum += norm<NormOne>(*iterCur);
        }
        return sum;
    }
};

template <class X1, class X2>
struct NormFunctor<NormOne,MultipleMatrix<X1,X2> >
{
    double operator () (MultipleMatrix<X1,X2> const& m) const
    {
        //return norm<NormOne>(m.getMatrix1()) + norm<NormOne>(m.getMatrix1());
        return norm<NormOne>(m.getMatrix1() + m.getMatrix1());
    }
};

template <class M, class T, class P>
struct NormFunctor<NormTwo, Matrix<M,T,P>>
{
    double operator () (Matrix<M,T,P> const& m) const
    {
        typedef const Matrix<M,T,P> MatrixType;

        double sum(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            sum += std::pow(*iterCur,2);
        }
        return std::sqrt(sum);
    }
};

template <class M, class P>
struct NormFunctor<NormTwo,Matrix<M,DynamicMatrix,P> >
{
    double operator () (Matrix<M,DynamicMatrix,P> const& m) const
    {
        typedef const Matrix<M,DynamicMatrix,P> MatrixType;

        double sum(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            sum += std::pow(norm<NormTwo>(*iterCur),2);
        }
        return std::sqrt(sum);
    }
};

template <class X1, class X2>
struct NormFunctor<NormTwo, MultipleMatrix<X1,X2>>
{
    double operator () (MultipleMatrix<X1,X2> const& m) const
    {
        // subadditivity ||A + B|| <= ||A| + ||B|||
        //return std::sqrt(pow(norm<NormTwo>(m.getMatrix1()),2) + pow(norm<NormTwo>(m.getMatrix2()),2));
        return norm<NormTwo>(m.getMatrix1() + m.getMatrix2());
    }
};

template <class M, class T, class P>
struct NormFunctor<NormMax, Matrix<M,T,P>>
{
    double operator () (Matrix<M,T,P> const& m) const
    {
        typedef const Matrix<M,T,P> MatrixType;

        double norm(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            norm = std::max(norm, std::abs(*iterCur));
        }
        return norm;
    }
};

template <class M, class P>
struct NormFunctor<NormMax, Matrix<M,DynamicMatrix,P>>
{
    double operator () (Matrix<M,DynamicMatrix,P> const& m) const
    {
        typedef const Matrix<M,DynamicMatrix,P> MatrixType;

        double value(0.0);
        for (typename MatrixType::const_iterator iterCur(m.begin()), iterEnd(m.end());
            iterCur != iterEnd; ++iterCur)
        {
            value = std::max(value, norm<NormMax>(*iterCur));
        }
        return value;
    }
};

template <class X1, class X2>
struct NormFunctor<NormMax, MultipleMatrix<X1,X2>>
{
    double operator () (MultipleMatrix<X1,X2> const& m) const
    {
        //return std::max(norm<NormMax>(m.getMatrix1()), norm<NormMax>(m.getMatrix1()));
        return norm<NormMax>(m.getMatrix1() + m.getMatrix2());
    }
};

/// Functor for DynamicMatrix
template <class NormType, class T>
struct DynamicNormFunctor
{
    double operator () (DynamicMatrix const& ptrA) const
    {
        return NormFunctor<NormType, T>()(*std::static_pointer_cast<T>(ptrA));
    }
};

template <class NormType>
struct NormFunctor<NormType, DynamicMatrix>
{
    double operator () (DynamicMatrix const& ptrA) const
    {
        return exec_dyn<DynamicMatrixTypeList, DynamicNormFunctor, TypeList<NormType>,
            std::function<double(DynamicMatrix const&)>>(ptrA);
    }
};

} // namespace BlasBooster
