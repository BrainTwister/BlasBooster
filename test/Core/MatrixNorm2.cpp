// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Norm.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

/// Test fixture
template <typename T>
class MatrixNormTest : public ::testing::Test
{};

TYPED_TEST_CASE_P(MatrixNormTest);

 /// Test body
template <class TypeParam>
void test(Matrix<Dense, double> const& refA, double result)
{
	TypeParam A(refA);
	EXPECT_NEAR(result, norm<NormTwo>(refA), 1e-5);
}

using MyTypes = ::testing::Types<
    Matrix<Dense, double>,
	Matrix<Dense, float>,
    Matrix<Dense, double, Parameter<size_t, RowMajor>>,
    Matrix<Sparse, double>,
    Matrix<Sparse, double, Parameter<size_t, RowMajor>>
	//DynamicMatrix
>;

TYPED_TEST_P(MatrixNormTest, Test1)
{
	test<TypeParam>({{1e-12, 1e-6}, {1e-6, 1e-12}}, 1.41421e-06);
}

TYPED_TEST_P(MatrixNormTest, Test2)
{
	test<TypeParam>({{1,2,3}, {4,5,6}}, 9.5393920141694561);
}

REGISTER_TYPED_TEST_CASE_P(MatrixNormTest, Test1, Test2);

INSTANTIATE_TYPED_TEST_CASE_P(My, MatrixNormTest, MyTypes);
