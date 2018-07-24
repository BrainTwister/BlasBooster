#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/BlockedMatrixGenerator.h"
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
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0}
    };

    auto&& C = (A * A).template execute<TheBestPolicy>();

    std::vector<size_t> blocks{2,2};

    auto&& bA = BlockedMatrixGenerator()(A, blocks, blocks, Threshold());

    auto&& bC = (bA * bA).template execute<TheBestPolicy>();

    std::cout << bC << std::endl;

	EXPECT_NEAR(0.0, norm<NormMax>(C - Matrix<Dense, double>(bC)), 1e-6) << C;
}
