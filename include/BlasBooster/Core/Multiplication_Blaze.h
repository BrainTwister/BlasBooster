#pragma once

#include <blaze/Math.h>
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Utilities/Tracker.h"

namespace BlasBooster {

struct Blaze {};

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via Blaze
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,Blaze>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
    	[[maybe_unused]] Tracker<TrackerID::Blaze_dgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        using MatrixType = blaze::CustomMatrix<double, blaze::aligned, blaze::padded, blaze::columnMajor>;

        MatrixType AA(const_cast<double*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns(), A.getNbRows());
        MatrixType BB(const_cast<double*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns(), B.getNbRows());
        MatrixType CC(C.getDataPointer(), C.getNbRows(), C.getNbColumns(), C.getNbRows());

        CC = AA * BB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,float> via Blaze
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,Blaze>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,float,P>& C)
    {
    	[[maybe_unused]] Tracker<TrackerID::Blaze_sgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        using MatrixType = blaze::CustomMatrix<float, blaze::aligned, blaze::padded, blaze::columnMajor>;

        MatrixType AA(const_cast<float*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns(), A.getNbRows());
        MatrixType BB(const_cast<float*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns(), B.getNbRows());
        MatrixType CC(C.getDataPointer(), C.getNbRows(), C.getNbColumns(), C.getNbRows());

        CC = AA * BB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,double> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,double,P,Dense,double,P,Blaze>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
    	[[maybe_unused]] Tracker<TrackerID::Blaze_sdgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        using MatrixTypeFloat = blaze::CustomMatrix<float, blaze::aligned, blaze::padded, blaze::columnMajor>;
        using MatrixTypeDouble = blaze::CustomMatrix<double, blaze::aligned, blaze::padded, blaze::columnMajor>;

        MatrixTypeFloat AA(const_cast<float*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns(), A.getNbRows());
        MatrixTypeDouble BB(const_cast<double*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns(), B.getNbRows());
        MatrixTypeDouble CC(C.getDataPointer(), C.getNbRows(), C.getNbColumns(), C.getNbRows());

        CC = AA * BB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,float> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,float,P,Dense,double,P,Blaze>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,double,P>& C)
    {
    	[[maybe_unused]] Tracker<TrackerID::Blaze_dsgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(),B.getNbColumns());

        using MatrixTypeFloat = blaze::CustomMatrix<float, blaze::aligned, blaze::padded, blaze::columnMajor>;
        using MatrixTypeDouble = blaze::CustomMatrix<double, blaze::aligned, blaze::padded, blaze::columnMajor>;

        MatrixTypeDouble AA(const_cast<double*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns(), A.getNbRows());
        MatrixTypeFloat BB(const_cast<float*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns(), B.getNbRows());
        MatrixTypeDouble CC(C.getDataPointer(), C.getNbRows(), C.getNbColumns(), C.getNbRows());

        CC = AA * BB;
    }
};

} // namespace BlasBooster
