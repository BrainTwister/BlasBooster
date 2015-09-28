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
class MatrixNorm : public ::testing::Test
{};

TYPED_TEST_CASE_P(MatrixNorm);

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
    //Matrix<Dense, double, Parameter<size_t, RowMajor>>,
    Matrix<Sparse, double>,
    Matrix<Sparse, double, Parameter<size_t, RowMajor>>
	//DynamicMatrix
>;

TYPED_TEST_P(MatrixNorm, Test1)
{
	test<TypeParam>({{1e-12, 1e-6}, {1e-6, 1e-12}}, 1.41421e-06);
}

REGISTER_TYPED_TEST_CASE_P(MatrixNorm, Test1);

INSTANTIATE_TYPED_TEST_CASE_P(My, MatrixNorm, MyTypes);
