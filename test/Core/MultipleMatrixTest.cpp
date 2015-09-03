// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/Multiplication.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

class MultipleMatrixTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	M1.resize(3, 3, ContinuousNumberFiller());

    	std::shared_ptr<Matrix<Sparse, double>> ptrM1(new Matrix<Sparse, double>(3, 3, 0, ContinuousNumberFiller()));
    	std::shared_ptr<Matrix<Sparse, float>> ptrM2(new Matrix<Sparse, float>(3, 3, 0, ContinuousNumberFiller()));

    	M2.reset(ptrM1, ptrM2);
    }

	Matrix<Dense, double> M1;
	MultipleMatrix<Matrix<Sparse, double>, Matrix<Sparse, float>> M2;
};

TEST_F(MultipleMatrixTest, Addition)
{
	auto M3 = M1 + M2;
	auto M4 = M1 + M1 + M1;

	EXPECT_TRUE(M3.equal(M4)) << "Matrix<Dense,double> + MultipleMatrix< Matrix<Sparse,double>, Matrix<Sparse,float> >";
}

TEST_F(MultipleMatrixTest, Multiplication)
{
	auto M3 = (M1 * M2).template execute<Native>();
	auto M4 = (M1 * (M1 + M1)).template execute<Native>();

	EXPECT_TRUE(M3.equal(M4)) << "Matrix<Dense,double> * MultipleMatrix< Matrix<Sparse,double>, Matrix<Sparse,float> >";
}

TEST_F(MultipleMatrixTest, NormOne)
{
	EXPECT_DOUBLE_EQ(norm<NormOne>(M1 + M1), norm<NormOne>(M2));
}

TEST_F(MultipleMatrixTest, NormTwo)
{
	EXPECT_DOUBLE_EQ(norm<NormTwo>(M1 + M1), norm<NormTwo>(M2));
}

TEST_F(MultipleMatrixTest, NormMax)
{
	EXPECT_DOUBLE_EQ(norm<NormMax>(M1 + M1), norm<NormMax>(M2));
}
