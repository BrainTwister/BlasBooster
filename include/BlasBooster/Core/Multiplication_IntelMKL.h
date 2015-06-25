// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef MULTIPLICATION_INTELMKL_H_
#define MULTIPLICATION_INTELMKL_H_

#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
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

namespace BlasBooster {

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via extern BLAS dgemm
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,IntelMKL>
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

        BlasInterface<IntelMKL,dgemm>()(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};

/// Matrix multiplication specialized for Matrix<Dense,float> * Matrix<Dense,float> via extern BLAS sgemm
template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,IntelMKL>
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

        BlasInterface<IntelMKL,sgemm>()(&transA,&transB,&M,&N,&K,&alpha,pA,&LDA,pB,&LDB,&beta,pC,&LDC);
    }
};

} // namespace BlasBooster

#endif /* MULTIPLICATION_INTELMKL_H_ */

