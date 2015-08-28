// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef NORM_H_
#define NORM_H_

#include "../Utilities/TypeList.h"
#include "BlasBooster/Utilities/exec_if.h"
#include "BlasBooster/Utilities/TypeChecker.h"
#include <functional>

namespace BlasBooster {

/// Primary template for NormFunctor
template <class NormType, class MatrixType>
struct NormFunctor
{
    double operator () (MatrixType const& A)
    {
        static_assert(wrong_t<MatrixType>::value, "Primary template must not be instantiated.");
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
    double operator () (Matrix<M,T,P> const& m)
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
    double operator () (Matrix<M,DynamicMatrix,P> const& m)
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
    double operator () (MultipleMatrix<X1,X2> const& m)
    {
        return norm<NormOne>(m.getMatrix1()) + norm<NormOne>(m.getMatrix1());
    }
};

template <class M, class T, class P>
struct NormFunctor<NormTwo,Matrix<M,T,P> >
{
    double operator () (Matrix<M,T,P> const& m)
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
    double operator () (Matrix<M,DynamicMatrix,P> const& m)
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
struct NormFunctor<NormTwo,MultipleMatrix<X1,X2> >
{
    double operator () (MultipleMatrix<X1,X2> const& m)
    {
        // subadditivity ||A + B|| <= ||A| + ||B|||
        //return std::sqrt(pow(norm<NormTwo>(m.getMatrix1()),2) + pow(norm<NormTwo>(m.getMatrix2()),2));
        return norm<NormTwo>(m.getMatrix1() + m.getMatrix1());
    }
};

template <class M, class T, class P>
struct NormFunctor<NormMax,Matrix<M,T,P> >
{
    double operator () (Matrix<M,T,P> const& m)
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
struct NormFunctor<NormMax,Matrix<M,DynamicMatrix,P> >
{
    double operator () (Matrix<M,DynamicMatrix,P> const& m)
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
struct NormFunctor<NormMax, MultipleMatrix<X1,X2> >
{
    double operator () (MultipleMatrix<X1,X2> const& m)
    {
        return std::max(norm<NormMax>(m.getMatrix1()), norm<NormMax>(m.getMatrix1()));
    }
};

template <class NormType, class FunctionType, class... T>
struct DynFuncGenerator
{
    static FunctionType dynFunc[sizeof...(T)];
};

template <class NormType, class FunctionType, class... T>
FunctionType DynFuncGenerator<NormType, FunctionType, T...>::dynFunc[sizeof...(T)]
														   = { NormFunctor<Matrix<Dense,double>, NormType>() };

template <class NormType>
struct NormFunctor<NormType, DynamicMatrix>
 : DynFuncGenerator<NormType, std::function< double(DynamicMatrix const&) >, DynamicMatrixTypeList>
{
    double operator () (DynamicMatrix const& m) const
    {
        return this->dynFunc[m->getTypeIndex()](m);
    }
};

} // namespace BlasBooster

#endif /* NORM_H_ */
