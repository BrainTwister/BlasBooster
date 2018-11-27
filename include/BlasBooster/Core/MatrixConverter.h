#pragma once

#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/Threshold.h"
#include "BlasBooster/Utilities/exec_if.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/wrong_t.h"

namespace BlasBooster {

/// Functor checking if a matrix could be converted to a matrix type T
template <class MatrixType>
struct IsConvertible
{
    template <class M, class T, class P>
    bool operator () (Matrix<M,T,P> const& matrix, Threshold const& threshold) const
    {
        return matrix.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()))
            <= threshold.getOccupationThreshold<MatrixType,double>()
            and matrix.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<float>()))
            <= threshold.getOccupationThreshold<MatrixType,float>();
    }
};

/// Functor checking if a matrix could be converted to a matrix type T
template <class M, class T, class P>
struct IsConvertibleChecker
{
    IsConvertibleChecker(Matrix<M,T,P> const& matrix, Threshold const& threshold)
     : matrix_(matrix), threshold_(threshold)
    {}

    template <class DynamicMatrixType>
    bool operator () (DynamicMatrixType* = 0) const
    {
        return IsConvertible<DynamicMatrixType>()(matrix_,threshold_);
    }

private:

    Matrix<M,T,P> const& matrix_;

    Threshold const& threshold_;
};

/// Functor converting Matrix<M1,T1,P1> into Matrix<M2,T2,P2>
template <class M1, class T1, class P1, class DynamicMatrixType>
struct ConversionFunctor
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        static_assert(wrong_t<M1>::value, "ConversionFunctor: Primary template must not be instantiated.");
        return DynamicMatrix(nullptr);
    }
};

/// Functor converting Matrix<M1,T1,P1> into Matrix<Dense,T2,P2>
template <class M1, class T1, class P1, class T2, class P2>
struct ConversionFunctor<M1,T1,P1,Matrix<Dense,T2,P2> >
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        return DynamicMatrix(new Matrix<Dense,T2,P2>(matrix));
    }
};

/// Functor converting Matrix<M1,T1,P1> into Matrix<Sparse,double,P2>
template <class M1, class T1, class P1, class P2>
struct ConversionFunctor<M1,T1,P1,Matrix<Sparse,double,P2> >
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        return DynamicMatrix(new Matrix<Sparse,double,P2>(matrix,
            AbsoluteValueRangeChecker<double>(threshold.getSignificanceThreshold<float>())));
    }
};

/// Functor converting Matrix<M1,T1,P1> into Matrix<Sparse,T2,P2>
template <class M1, class T1, class P1, class P2>
struct ConversionFunctor<M1,T1,P1,Matrix<Sparse,float,P2> >
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        return DynamicMatrix(new Matrix<Sparse,float,P2>(matrix,
            AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(
                threshold.getSignificanceThreshold<double>(),threshold.getSignificanceThreshold<float>())));
    }
};

/// Functor converting Matrix<M1,T1,P1> into MultipleMatrix<X1,X2>
template <class M1, class T1, class P1, class X1, class X2>
struct ConversionFunctor<M1,T1,P1,MultipleMatrix<X1,X2> >
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        std::shared_ptr<X1> ptrX1(new X1(matrix,AbsoluteValueRangeChecker<double>(
                threshold.getSignificanceThreshold<float>())));
        std::shared_ptr<X2> ptrX2(new X2(matrix,AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(
                threshold.getSignificanceThreshold<double>(),threshold.getSignificanceThreshold<float>())));
        return DynamicMatrix(new MultipleMatrix<X1,X2>(ptrX1,ptrX2));
    }
};

/// Functor converting Matrix<M1,T1,P1> into Matrix<Zero>
template <class M1, class T1, class P1, class P2>
struct ConversionFunctor<M1,T1,P1,Matrix<Zero,P2>>
{
    DynamicMatrix operator () (Matrix<M1,T1,P1> const& matrix, Threshold const& threshold) const
    {
        return DynamicMatrix(new Matrix<Zero,P2>(matrix));
    }
};

/// Functor converting Matrix<M,T,P> into DynamicMatrixType
template <class M, class T, class P>
struct DynamicConversionFunctor
{
    typedef DynamicMatrix result_type;

    DynamicConversionFunctor(Matrix<M,T,P> const& matrix, Threshold const& threshold)
     : matrix_(matrix), threshold_(threshold)
    {}

    template <class DynamicMatrixType>
    result_type operator () (DynamicMatrixType* = 0) const
    {
        return ConversionFunctor<M,T,P,DynamicMatrixType>()(matrix_,threshold_);
    }

private:

    Matrix<M,T,P> const& matrix_;

    Threshold const& threshold_;
};

struct MatrixConverter
{
    template <class M, class T, class P>
    DynamicMatrix operator () (Matrix<M,T,P> const& matrix, Threshold const& threshold) const
    {
        return exec_if<DynamicMatrixTypeList>(
            IsConvertibleChecker<M,T,P>(matrix, threshold),
            DynamicConversionFunctor<M,T,P>(matrix, threshold)
        );
    }
};

} // namespace BlasBooster
