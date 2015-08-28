// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MULTIPLICATION_INTELMKL_H_
#define BLASBOOSTER_CORE_MULTIPLICATION_INTELMKL_H_

#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"

namespace BlasBooster {

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via extern BLAS dgemm
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(),B.getNbColumns());

        char n = 'N';
        double alpha = 1.0;
        double beta = 0.0;

        BlasInterface<IntelMKL,dgemm>()(
            &n,
            &n,
            reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &alpha,
            const_cast<double*>(A.data_),
            reinterpret_cast<const int*>(&A.nbRows_),
            const_cast<double*>(B.data_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &beta,
	    C.data_,
            reinterpret_cast<const int*>(&A.nbRows_)
        );
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

        char n = 'N';
        float alpha = 1.0f;
        float beta = 0.0f;

        BlasInterface<IntelMKL,sgemm>()(
            &n,
            &n,
            reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &alpha,
            const_cast<float*>(A.data_),
            reinterpret_cast<const int*>(&A.nbRows_),
            const_cast<float*>(B.data_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &beta,
            C.data_,
            reinterpret_cast<const int*>(&A.nbRows_)
        );
    }
};

#if 0
/// Matrix multiplication specialized for Matrix<Sparse,double> * Matrix<Sparse,double> via extern SPBLAS dcsrmm
template <class P>
struct MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,IntelMKL>
{
	char n = 'N';
	BlasInterface<IntelMKL,dcsrmm>()(char *transa, MKL_INT *m, MKL_INT *n, MKL_INT *k, double *alpha, char *matdescra,
		double  *val, MKL_INT *indx,  MKL_INT *pntrb, MKL_INT *pntre, double *b, MKL_INT *ldb, double *beta, double *c, MKL_INT *ldc);
}
#endif

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MULTIPLICATION_INTELMKL_H_
