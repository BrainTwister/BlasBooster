// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Multiplication.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

/// Test fixture
template <typename T>
class MatrixMatrixMultiplicationTest : public ::testing::Test
{

};

TYPED_TEST_CASE_P(MatrixMatrixMultiplicationTest);

 /// Test body
TYPED_TEST_P(MatrixMatrixMultiplicationTest, Basic)
{
	using TypeA = typename std::tuple_element<0, TypeParam>::type;
	using TypeB = typename std::tuple_element<1, TypeParam>::type;
	using TypeC = typename std::tuple_element<2, TypeParam>::type;
	using Interface = typename std::tuple_element<3, TypeParam>::type;

	Matrix<Dense, double> ref{{1,2},{3,4}};
	TypeA A(ref);
	TypeB B(ref);
	Matrix<Dense, double> C = (A * B).template execute<Interface>();

	Matrix<Dense, double> expected{{7,10},{15,22}};
	EXPECT_NEAR(0.0, norm<NormMax>(C - expected), 1e-6);
}

REGISTER_TYPED_TEST_CASE_P(MatrixMatrixMultiplicationTest, Basic);

typedef ::testing::Types<
    std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, IntelMKL>,
    std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, IntelMKL>,
	std::tuple<Matrix<Sparse, double>, Matrix<Sparse, double>, Matrix<Dense, double>, IntelMKL>
> MyTypes;

INSTANTIATE_TYPED_TEST_CASE_P(My, MatrixMatrixMultiplicationTest, MyTypes);
