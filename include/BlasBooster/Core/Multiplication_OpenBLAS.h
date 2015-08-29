// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MULTIPLICATION_OPENBLAS_H_
#define BLASBOOSTER_CORE_MULTIPLICATION_OPENBLAS_H_

#include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include <iostream>

namespace BlasBooster {

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via extern BLAS dgemm
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,OpenBLAS>
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

        std::cout << "Calling OpenBLAS dgemm " << M << " " << N << " " << K << std::endl;

        BlasInterface<OpenBLAS,dgemm>()(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,float> via extern BLAS sgemm
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,OpenBLAS>
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

        std::cout << "Calling OpenBLAS sgemm " << M << " " << N << " " << K << std::endl;

        BlasInterface<OpenBLAS,sgemm>()(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MULTIPLICATION_OPENBLAS_H_
