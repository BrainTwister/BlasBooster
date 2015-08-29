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

namespace {

struct TestDataStructure
{
	TestDataStructure(
        DynamicMatrix A,
        DynamicMatrix B,
        DynamicMatrix C
	): A(A), B(B), C(C)
	{}

    DynamicMatrix A;
    DynamicMatrix B;
    DynamicMatrix C;
};

} // namespace anonymous

/// Test fixture for MatrixMultiplicationTest
class MatrixMultiplicationTest
 : public ::testing::WithParamInterface<TestDataStructure>,
   public ::testing::Test
{};

 /// Test body for MatrixMultiplicationTest
TEST_P(MatrixMultiplicationTest, Basic)
{
    GetParam().A * GetParam().B;
    //EXPECT_EQ(GetParam().C, GetParam().A * GetParam().B);
}

INSTANTIATE_TEST_CASE_P(AllMatrixMultiplicationTests, MatrixMultiplicationTest,
	::testing::Values(
        TestDataStructure(
            DynamicMatrix(new Matrix<Dense,double>(3,3,ContinuousNumberFiller())),
            DynamicMatrix(new Matrix<Dense,double>(3,3,ContinuousNumberFiller())),
            DynamicMatrix(new Matrix<Dense,double>(3,3,ContinuousNumberFiller()))
        )
    )
);
