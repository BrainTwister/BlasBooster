#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "BlasBooster/Core/Norm.h"
#include "BlasBooster/Core/Transposition.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

/// Test fixture
template <typename T>
class TranspositionTest : public ::testing::Test
{};

TYPED_TEST_SUITE_P(TranspositionTest);

 /// Test body
template <class TypeParam>
void test2(Matrix<Dense, int> const& A, Matrix<Dense, int> const& AT)
{
    Matrix<Dense, int> result(transpose(TypeParam(A)));
//	std::cout << A << std::endl;
//	std::cout << TypeParam(A) << std::endl;
//	std::cout << transpose(TypeParam(A)) << std::endl;
//	std::cout << result << std::endl;
    EXPECT_NEAR(0.0, norm<NormTwo>(result - AT), 1e-5) << A << TypeParam(A) << transpose(TypeParam(A)) << result;
}

using MyTypes = ::testing::Types<
    Matrix<Dense, int>,
    Matrix<Dense, int, Parameter<size_t, RowMajor>>,
    Matrix<Sparse, int>
    //Matrix<Sparse, int, Parameter<size_t, RowMajor>>
    //DynamicMatrix
>;

TYPED_TEST_P(TranspositionTest, Test1)
{
    test2<TypeParam>({{1, 2}, {3, 4}}, {{1, 3}, {2, 4}});
}

TYPED_TEST_P(TranspositionTest, Test2)
{
    test2<TypeParam>({{1, 2, 3}, {4, 5, 6}}, {{1, 4}, {2, 5}, {3, 6}});
}

REGISTER_TYPED_TEST_SUITE_P(TranspositionTest, Test1, Test2);

INSTANTIATE_TYPED_TEST_SUITE_P(My, TranspositionTest, MyTypes);
