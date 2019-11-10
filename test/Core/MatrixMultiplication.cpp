#include "BlasBooster/Core/AllMatrixTypes.h"

#include "gtest/gtest.h"

using namespace BlasBooster;

TEST(MatrixMatrixMultiplicationTest, DenseDouble)
{
    Matrix<Dense, double> A{
        {2.0, 3.0},
        {4.0, 1.0}
    };
    auto B = A;
    Matrix<Dense, double> C = A * B;

    EXPECT_EQ(16.0, C(0,0));
}

TEST(MatrixMatrixMultiplicationTest, DynamicMatrix)
{
	auto A = std::make_shared<Matrix<Dense, double>>();
    auto B = A;
    auto C = (A * B).template execute<Native>();

    EXPECT_EQ(16.0, *C(0,0));
}
