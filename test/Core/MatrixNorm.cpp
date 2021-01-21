#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Norm.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

namespace {

struct TestDataStructure
{
    TestDataStructure(Matrix<Dense,double> const& matrix, double result): matrix(matrix), result(result) {}

    Matrix<Dense,double> matrix;
    double result;
};

} // namespace anonymous

/// Test fixture for MatrixMultiplicationTest
class MatrixNorm
 : public ::testing::WithParamInterface<TestDataStructure>,
   public ::testing::Test
{};

 /// Test body for MatrixMultiplicationTest
TEST_P(MatrixNorm, DenseDouble)
{
    EXPECT_NEAR(GetParam().result, norm<NormTwo>(GetParam().matrix), 1e-5);
}

/// Test body for MatrixMultiplicationTest
TEST_P(MatrixNorm, DynamicMatrix)
{
    DynamicMatrix dynMat(new Matrix<Dense,double>(GetParam().matrix));
    EXPECT_NEAR(GetParam().result, norm<NormTwo>(dynMat), 1e-5);
}

INSTANTIATE_TEST_SUITE_P(AllMatrixNormTests, MatrixNorm,
    ::testing::Values(
        TestDataStructure(
            {{ 1e-12, 1e-6 }, { 1e-6, 1e-12 }}, 1.41421e-06
        )
    )
);
