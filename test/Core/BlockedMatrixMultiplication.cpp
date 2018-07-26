#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
#include "BlasBooster/Core/GenerateTypeMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_Native.h"
#include "BlasBooster/Core/Multiplication_TheBestPolicy.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

TEST(BlockMatrixMatrixMultiplicationTest, Test1)
{
    Matrix<Dense, double> A{
    	{2.0, 3.0, 0.0, 0.0},
    	{4.0, 1.0, 0.0, 0.0},
    	{0.0, 0.0, 2e-7, 3e-7},
    	{0.0, 0.0, 4e-7, 1e-7}
    };

    auto&& C = (A * A).template execute<TheBestPolicy>();

    std::vector<size_t> blocks{2,2};

    auto&& bA = BlockedMatrixGenerator()(A, blocks, blocks, Threshold());

    EXPECT_EQ(6, bA(0,0)->getTypeIndex());
    EXPECT_EQ(0, bA(0,1)->getTypeIndex());
    EXPECT_EQ(2, std::static_pointer_cast<Matrix<Zero>>(bA(0,1))->getNbRows());

    auto&& bC = (bA * bA).template execute<TheBestPolicy>();

    EXPECT_EQ(6, bC(0,0)->getTypeIndex());
    EXPECT_EQ(0, bC(0,1)->getTypeIndex());
    EXPECT_EQ(2, std::static_pointer_cast<Matrix<Zero>>(bC(0,1))->getNbRows());

    auto&& CC = Matrix<Dense, double>(bC);

	EXPECT_NEAR(0.0, norm<NormMax>(C - CC), 1e-6) << C << "\n" << CC;
}
