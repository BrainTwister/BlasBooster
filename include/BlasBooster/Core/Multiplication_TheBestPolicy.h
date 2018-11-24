#pragma once

#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_Native.h"

#ifdef WITH_INTELMKL
    #include "BlasBooster/Core/Multiplication_IntelMKL.h"
#endif

#ifdef WITH_OPENBLAS
    #include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#endif

namespace BlasBooster {

struct TheBestPolicy {};

/// The general case of TheBestPolicy is the Native multiplication
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3>
struct MultiplicationFunctor<M1,T1,P1,M2,T2,P2,M3,T3,P3,TheBestPolicy>
 : public MultiplicationFunctor<M1,T1,P1,M2,T2,P2,M3,T3,P3,Native>
{};

#ifdef WITH_INTELMKL

template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{};

template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,IntelMKL>
{};

template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,double,P,Dense,double,P,TheBestPolicy>
{
    void operator () (Matrix<Dense,float,P> const& A, Matrix<Dense,double,P> const& B, Matrix<Dense,double,P>& C)
    {
    	Matrix<Dense,float,P> fC;
    	MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,IntelMKL>()(
            A, Matrix<Dense,float,P>(B), fC);
    	C = fC;
	}
};

template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,float,P,Dense,double,P,TheBestPolicy>
{
    void operator () (Matrix<Dense,double,P> const& A, Matrix<Dense,float,P> const& B, Matrix<Dense,double,P>& C)
    {
    	Matrix<Dense,float,P> fC;
    	MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,IntelMKL>()(
            Matrix<Dense,float,P>(A), B, fC);
    	C = fC;
	}
};

template <class P>
struct MultiplicationFunctor<Sparse,double,P,Dense,double,P,Dense,double,P,TheBestPolicy>
 : public MultiplicationFunctor<Sparse,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{};

//template <class P>
//struct MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,TheBestPolicy>
// : public MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,IntelMKL>
//{};

#elif WITH_OPENBLAS

template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,OpenBLAS>
{};

template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,OpenBLAS>
{};

#endif // WITH_OPENBLAS

} // namespace BlasBooster
