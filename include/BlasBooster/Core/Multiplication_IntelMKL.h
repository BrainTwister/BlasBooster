#pragma once

#include <algorithm>
#include <iostream>
#include <type_traits>

#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/SparseMatrix.h"

namespace BlasBooster {

/// Matrix multiplication specialized for Matrix<Dense,T> * Matrix<Dense,T>
template <class T, class P>
struct MultiplicationFunctor<Dense,T,P,Dense,T,P,Dense,T,P,IntelMKL>
{
    void operator () (Matrix<Dense,T,P> const& A, Matrix<Dense,T,P> const& B, Matrix<Dense,T,P>& C)
    {
    	typedef typename std::conditional<std::is_same<T, double>::value, dgemm, sgemm>::type FuncType;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

        char n = 'N';
        T alpha = 1.0;
        T beta = 0.0;

        BlasInterface<IntelMKL, FuncType>()(
            &n,
            &n,
            reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &alpha,
            const_cast<T*>(A.data_),
            reinterpret_cast<const int*>(&A.nbRows_),
            const_cast<T*>(B.data_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            &beta,
	        C.data_,
            reinterpret_cast<const int*>(&A.nbRows_)
        );
    }
};

/// Matrix multiplication specialized for Matrix<Sparse,T> * Matrix<Dense,T>
template <class T, class P>
struct MultiplicationFunctor<Sparse,T,P,Dense,T,P,Dense,T,P,IntelMKL>
{
    void operator () (Matrix<Sparse,T,P> const& A, Matrix<Dense,T,P> const& B, Matrix<Dense,T,P>& C)
    {
    	typedef typename std::conditional<std::is_same<T, double>::value, dcsrmm, scsrmm>::type FuncType;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

		char n = 'N';
		// one-based indexing matdescra[3] = 'F' => B and C must be column-major
		// zero-based indexing matdescra[3] = 'C' => B and C must be row-major
		char matdescra[6] = {'G', 'L', 'N', 'F', 'X', 'X'};
        T alpha = 1.0;
        T beta = 0.0;

        // TODO: Add parameter for index-base
        Matrix<Sparse, T, Parameter<size_t, RowMajor>> rmA(A);

        std::vector<int> rmA_key(rmA.key_.size());
        std::transform(rmA.key_.begin(), rmA.key_.end(), rmA_key.begin(), [](size_t value){
            return ++value;
        });

        std::vector<int> rmA_offset(rmA.offset_.size());
        std::transform(rmA.offset_.begin(), rmA.offset_.end(), rmA_offset.begin(), [](size_t value){
            return ++value;
        });

		BlasInterface<IntelMKL, FuncType>()(
			&n,
            reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			&alpha,
			matdescra,
			const_cast<T*>(rmA.value_.getDataPointer()),
			&rmA_key[0],
			&rmA_offset[0],
			&rmA_offset[1],
			const_cast<T*>(B.data_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			&beta,
			C.data_,
            reinterpret_cast<const int*>(&A.nbRows_)
		);
    }
};

/// Matrix multiplication specialized for Matrix<Sparse,T> * Matrix<Sparse,T>
template <class T, class P>
struct MultiplicationFunctor<Sparse,T,P,Sparse,T,P,Sparse,T,P,IntelMKL>
{
    void operator () (Matrix<Sparse,T,P> const& A, Matrix<Sparse,T,P> const& B, Matrix<Sparse,T,P>& C)
    {
    	typedef typename std::conditional<std::is_same<T, double>::value, dcsrmultcsr, scsrmultcsr>::type FuncType;

        assert(A.getNbColumns() == B.getNbRows());
        C.resize(A.getNbRows(), B.getNbColumns());

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

		BlasInterface<IntelMKL, FuncType>()(
			&n,
			&request,
			&sort,
			reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&A.nbColumns_),
            reinterpret_cast<const int*>(&B.nbColumns_),
			const_cast<T*>(A.value_.getDataPointer()),
			&A_key[0],
			&A_offset[0],
			const_cast<T*>(B.value_.getDataPointer()),
			&B_key[0],
			&B_offset[0],
			const_cast<T*>(C.value_.getDataPointer()),
			&C_key[0],
			&C_offset[0],
			reinterpret_cast<const int*>(C.value_.size()),
			&info
		);
        assert(info == 0);

        request = 2;
		BlasInterface<IntelMKL, FuncType>()(
			&n,
			&request,
			&sort,
			reinterpret_cast<const int*>(&A.nbRows_),
            reinterpret_cast<const int*>(&B.nbColumns_),
            reinterpret_cast<const int*>(&A.nbColumns_),
			const_cast<T*>(A.value_.getDataPointer()),
			&A_key[0],
			&A_offset[0],
			const_cast<T*>(B.value_.getDataPointer()),
			&B_key[0],
			&B_offset[0],
			const_cast<T*>(C.value_.getDataPointer()),
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
    }
};

} // namespace BlasBooster
