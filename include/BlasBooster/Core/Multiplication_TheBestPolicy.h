// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_MULTIPLICATION_THEBESTPOLICY_H_
#define BLASBOOSTER_CORE_MULTIPLICATION_THEBESTPOLICY_H_

#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/Multiplication_Native.h"

namespace BlasBooster {

struct TheBestPolicy {};

/// The general case of TheBestPolicy is the Native multiplication
template <class M1, class T1, class P1,
          class M2, class T2, class P2,
          class M3, class T3, class P3>
struct MultiplicationFunctor<M1,T1,P1,M2,T2,P2,M3,T3,P3,TheBestPolicy>
 : public MultiplicationFunctor<M1,T1,P1,M2,T2,P2,M3,T3,P3,Native>
{};

template <class P>
struct MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,double,P,Dense,double,P,Dense,double,P,OpenBLAS>
{};

template <class P>
struct MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,TheBestPolicy>
 : public MultiplicationFunctor<Dense,float,P,Dense,float,P,Dense,float,P,OpenBLAS>
{};

template <class P>
struct MultiplicationFunctor<Sparse,double,P,Dense,double,P,Dense,double,P,TheBestPolicy>
 : public MultiplicationFunctor<Sparse,double,P,Dense,double,P,Dense,double,P,IntelMKL>
{};

//template <class P>
//struct MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,TheBestPolicy>
// : public MultiplicationFunctor<Sparse,double,P,Sparse,double,P,Sparse,double,P,IntelMKL>
//{};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_MULTIPLICATION_THEBESTPOLICY_H_
