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

namespace {

template <typename T>
class MatrixNorm : public ::testing::Test
{};

using MyTypes = ::testing::Types<
    Matrix<Dense,double>,
	Matrix<Dense,float>,
	DynamicMatrix
>;

} // anonymous namespace

TYPED_TEST_CASE_P(MatrixNorm);

TYPED_TEST_P(MatrixNorm, CheckResult)
{
    TypeParam A;
    EXPECT_EQ(1.0, norm<NormTwo>(A));
}

REGISTER_TYPED_TEST_CASE_P(MatrixNorm, CheckResult);

INSTANTIATE_TYPED_TEST_CASE_P(My, MatrixNorm, MyTypes);
