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

/// \brief Functors for the Intel MKL interface.
/// The interface has more the meaning of a namespace. A struct is taken to use it as template parameter.
struct IntelMKL {

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

} // namespace IntelMKL

} // namespace BlasBooster

#endif /* MULTIPLICATION_H_ */

