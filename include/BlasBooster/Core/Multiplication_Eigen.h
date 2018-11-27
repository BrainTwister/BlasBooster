#pragma once

#include <Eigen/Dense>
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Utilities/Tracker.h"

namespace BlasBooster {

struct EigenI {};

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,EigenI>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        [[maybe_unused]] Tracker<TrackerID::Eigen_dgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        Eigen::Map<Eigen::MatrixXd> eA(const_cast<double*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns());
        Eigen::Map<Eigen::MatrixXd> eB(const_cast<double*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns());
        Eigen::Map<Eigen::MatrixXd> eC(C.getDataPointer(), C.getNbRows(), C.getNbColumns());

        eC = eA * eB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,float> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,EigenI>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,float,P>& C)
    {
        [[maybe_unused]] Tracker<TrackerID::Eigen_sgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(),B.getNbColumns());


        Eigen::Map<Eigen::MatrixXf> eA(const_cast<float*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns());
        Eigen::Map<Eigen::MatrixXf> eB(const_cast<float*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns());
        Eigen::Map<Eigen::MatrixXf> eC(C.getDataPointer(), C.getNbRows(), C.getNbColumns());

        eC = eA * eB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,double> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,double,P,Dense,double,P,EigenI>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        [[maybe_unused]] Tracker<TrackerID::Eigen_sdgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        Eigen::Map<Eigen::MatrixXf> eA(const_cast<float*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns());
        Eigen::Map<Eigen::MatrixXd> eB(const_cast<double*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns());
        Eigen::Map<Eigen::MatrixXd> eC(C.getDataPointer(), C.getNbRows(), C.getNbColumns());

        eC = eA * eB;
    }
};

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,float> via Eigen
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,float,P,Dense,double,P,EigenI>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,double,P>& C)
    {
        [[maybe_unused]] Tracker<TrackerID::Eigen_dsgemm> tracker;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(),B.getNbColumns());


        Eigen::Map<Eigen::MatrixXd> eA(const_cast<double*>(A.getDataPointer()), A.getNbRows(), A.getNbColumns());
        Eigen::Map<Eigen::MatrixXf> eB(const_cast<float*>(B.getDataPointer()), B.getNbRows(), B.getNbColumns());
        Eigen::Map<Eigen::MatrixXd> eC(C.getDataPointer(), C.getNbRows(), C.getNbColumns());

        eC = eA * eB;
    }
};

} // namespace BlasBooster
