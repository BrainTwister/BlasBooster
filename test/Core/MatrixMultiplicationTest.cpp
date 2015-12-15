// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_Native.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

/// Test fixture
template <typename T>
class MatrixMatrixMultiplicationTest : public ::testing::Test
{};

TYPED_TEST_CASE_P(MatrixMatrixMultiplicationTest);

 /// Test body
template <class TypeParam>
void test(Matrix<Dense, double> const& refA, Matrix<Dense, double> const& refB, Matrix<Dense, double> const& refC)
{
	using TypeA = typename std::tuple_element<0, TypeParam>::type;
	using TypeB = typename std::tuple_element<1, TypeParam>::type;
	//using TypeC = typename std::tuple_element<2, TypeParam>::type;
	using Interface = typename std::tuple_element<3, TypeParam>::type;

	TypeA A(refA);
	TypeB B(refB);
	Matrix<Dense, double> C = (A * B).template execute<Interface>();

	EXPECT_NEAR(0.0, norm<NormMax>(C - refC), 1e-6) << C;
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test1)
{
	test<TypeParam>({{1,2},{3,4}}, {{1,2},{3,4}}, {{7,10},{15,22}});
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test2)
{
	test<TypeParam>({{1,2,3},{4,5,6}}, {{1,2},{3,4},{5,6}}, {{22,28},{49,64}});
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test3)
{
	test<TypeParam>({{1,2,3}}, {{1,2},{3,4},{5,6}}, {{22,28}});
}

REGISTER_TYPED_TEST_CASE_P(MatrixMatrixMultiplicationTest, Test1, Test2, Test3);

typedef ::testing::Types<
	std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, Native>
	,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, Native>
	,std::tuple<Matrix<Sparse, double>, Matrix<Dense, double>, Matrix<Dense, double>, Native>
    //,std::tuple<Matrix<Sparse, double>, Matrix<Sparse, double>, Matrix<Sparse, double>, Native>
#ifdef USE_INTEL_MKL
    ,std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, IntelMKL>
    ,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, IntelMKL>
	,std::tuple<Matrix<Sparse, double>, Matrix<Dense, double>, Matrix<Dense, double>, IntelMKL>
	//,std::tuple<Matrix<Sparse, double>, Matrix<Sparse, double>, Matrix<Sparse, double>, IntelMKL>
#endif
> MyTypes;

INSTANTIATE_TYPED_TEST_CASE_P(My, MatrixMatrixMultiplicationTest, MyTypes);
