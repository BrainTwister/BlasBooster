#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/BinaryFunctors.h"
#include "BlasBooster/Core/Norm.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

namespace {

struct TestDataStructure
{
    TestDataStructure(Matrix<Dense,double> const& A, Matrix<Dense,double> const& B, Matrix<Dense,double> const& C)
     : A(A), B(B), C(C)
    {}

    Matrix<Dense, double> A;
    Matrix<Dense, double> B;
    Matrix<Dense, double> C;
};

} // namespace anonymous

/// Test fixture for MatrixMultiplicationTest
class BinaryFunctors
 : public ::testing::WithParamInterface<TestDataStructure>,
   public ::testing::Test
{};

 /// Test body for MatrixMultiplicationTest
TEST_P(BinaryFunctors, StaticDenseDouble)
{
    EXPECT_NEAR(0.0, norm<NormTwo>(GetParam().A + GetParam().B - GetParam().C), 1e-6);
}

/// Test body for MatrixMultiplicationTest
TEST_P(BinaryFunctors, DynamicDenseDouble)
{
    DynamicMatrix dynA(new Matrix<Dense, double>(GetParam().A));
    DynamicMatrix dynB(new Matrix<Dense, double>(GetParam().B));
    DynamicMatrix dynC(new Matrix<Dense, double>(GetParam().C));
    EXPECT_NEAR(0.0, norm<NormTwo>(dynA + dynB - dynC), 1e-6);
}

INSTANTIATE_TEST_CASE_P(AllBinaryFunctorsTests, BinaryFunctors,
    ::testing::Values(
        TestDataStructure(
            {{ 1.0, 2.0 }, { -4.0, 3.0 }},
            {{ 1.0, 2.0 }, { -4.0, 3.0 }},
            {{ 2.0, 4.0 }, { -8.0, 6.0 }}
        )
    )
);
