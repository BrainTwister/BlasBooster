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
#include <algorithm>
#include <iostream>

namespace BlasBooster {

/// Matrix multiplication specialized for Matrix<Dense,double> * Matrix<Dense,double> via extern BLAS dgemm
template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(), B.getNbColumns());

        char n = 'N';
        double alpha = 1.0;
        double beta = 0.0;

        BlasInterface<IntelMKL, dgemm>()(
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

        C.resize(A.getNbRows(), B.getNbColumns());

        char n = 'N';
        float alpha = 1.0f;
        float beta = 0.0f;

        BlasInterface<IntelMKL, sgemm>()(
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

/// Matrix multiplication specialized for Matrix<Sparse,double> * Matrix<Dense,double> via extern SPBLAS dcsrmm
template <class P>
struct MultiplicationFunctor<Sparse,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{
    void operator () (Matrix<Sparse,double,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(), B.getNbColumns());

		char n = 'N';
		char matdescra[6] = {'G', 'L', 'N', 'C', 'X', 'X'};
        double alpha = 1.0;
        double beta = 0.0;

		BlasInterface<IntelMKL, dcsrmm>()(
			&n,
            reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			&alpha,
			matdescra,
			const_cast<double*>(A.value_.getDataPointer()),
			const_cast<int*>(reinterpret_cast<const int*>(A.key_.getDataPointer())),
			const_cast<int*>(reinterpret_cast<const int*>(A.offset_.getDataPointer())),
			const_cast<int*>(reinterpret_cast<const int*>(A.offset_.getDataPointer() + 1)),
			const_cast<double*>(B.data_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			&beta,
			C.data_,
            reinterpret_cast<const int*>(&A.nbRows_)
		);
    }
};

/// Matrix multiplication specialized for Matrix<Sparse,double> * Matrix<Sparse,double> via extern SPBLAS dcsrmultcsr
template <class P>
struct MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,IntelMKL>
{
    void operator () (Matrix<Sparse,double,P> const& A, Matrix<Sparse,double,P> const& B, Matrix<Sparse,double,P>& C)
    {
        if (A.getNbColumns() != B.getNbRows()) BLASBOOSTER_CORE_FAILURE("wrong dimension");

        C.resize(A.getNbRows(), B.getNbColumns());
        std::cout << "A" << A << std::endl;
        std::cout << "B" << B << std::endl;

	    char n = 'N';
        int request = 1;
        int sort = 8;
        int info;

        std::vector<int> A_key(A.key_.size());
        std::transform(A.key_.begin(), A.key_.end(), A_key.begin(), [](size_t value){
            return ++value;
        });

        std::vector<int> A_offset(A.offset_.size());
        std::transform(A.offset_.begin(), A.offset_.end(), A_offset.begin(), [](size_t value){
            return ++value;
        });

        std::vector<int> B_key(B.key_.size());
        std::transform(B.key_.begin(), B.key_.end(), B_key.begin(), [](size_t value){
            return ++value;
        });

        std::vector<int> B_offset(B.offset_.size());
        std::transform(B.offset_.begin(), B.offset_.end(), B_offset.begin(), [](size_t value){
            return ++value;
        });

        std::vector<int> C_key(C.key_.size());
        std::vector<int> C_offset(C.offset_.size());

		BlasInterface<IntelMKL, dcsrmultcsr>()(
			&n,
			&request,
			&sort,
			reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            reinterpret_cast<const int*>(&B.nbColumns_),
			const_cast<double*>(A.value_.getDataPointer()),
			&A_key[0],
			&A_offset[0],
			const_cast<double*>(B.value_.getDataPointer()),
			&B_key[0],
			&B_offset[0],
			const_cast<double*>(C.value_.getDataPointer()),
			&C_key[0],
			&C_offset[0],
			reinterpret_cast<const int*>(C.value_.size()),
			&info
		);
        assert(info == 0);

        request = 2;
		BlasInterface<IntelMKL, dcsrmultcsr>()(
			&n,
			&request,
			&sort,
			reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			const_cast<double*>(A.value_.getDataPointer()),
			&A_key[0],
			&A_offset[0],
			const_cast<double*>(B.value_.getDataPointer()),
			&B_key[0],
			&B_offset[0],
			const_cast<double*>(C.value_.getDataPointer()),
			&C_key[0],
			&C_offset[0],
			reinterpret_cast<const int*>(C.value_.size()),
			&info
		);
        assert(info == 0);

        std::transform(C_key.begin(), C_key.end(), C.key_.begin(), [](int value){
            return --value;
        });

        std::transform(C_offset.begin(), C_offset.end(), C.offset_.begin(), [](int value){
            return --value;
        });
        std::cout << "hey" << C << std::endl;
    }
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MULTIPLICATION_INTELMKL_H_
