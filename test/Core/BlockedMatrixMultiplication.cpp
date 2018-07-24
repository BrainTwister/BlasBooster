#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_Native.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test1)
{
    Matrix<Dense, double> A{
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0},
    	{2.0, 3.0, 1.0, 2.0}
    };

    std::vector<size_t> blocks{2,2};

    auto&& B = BlockedMatrixGenerator()(refB, blocks, blocks, threshold);

    auto&& C = (B * B).template execute<TheBestPolicy>();
}
