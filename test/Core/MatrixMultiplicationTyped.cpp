#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Multiplication_Blaze.h"
#ifdef WITH_EIGEN
#include "BlasBooster/Core/Multiplication_Eigen.h"
#endif
#include "BlasBooster/Core/Multiplication_IntelMKL.h"
#include "BlasBooster/Core/Multiplication_Native.h"
#include "BlasBooster/Core/Multiplication_OpenBLAS.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

/// Test fixture
template <typename T>
class MatrixMatrixMultiplicationTest : public ::testing::Test
{};

TYPED_TEST_SUITE_P(MatrixMatrixMultiplicationTest);

 /// Test body
template <class TypeParam>
void test(Matrix<Dense, double> const& refA, Matrix<Dense, double> const& refB, Matrix<Dense, double> const& refC)
{
    using TypeA = typename std::tuple_element<0, TypeParam>::type;
    using TypeB = typename std::tuple_element<1, TypeParam>::type;
    using TypeC = typename std::tuple_element<2, TypeParam>::type;
    using Interface = typename std::tuple_element<3, TypeParam>::type;

    TypeA A(refA);
    TypeB B(refB);
    TypeC C;

    MultiplicationFunctor<typename TypeA::matrix_type, typename TypeA::value_type, typename TypeA::parameter,
	                      typename TypeB::matrix_type, typename TypeB::value_type, typename TypeB::parameter,
	                      typename TypeC::matrix_type, typename TypeC::value_type, typename TypeC::parameter,
	                      Interface>()(A, B, C);

    Matrix<Dense, double> resC(C);
    EXPECT_NEAR(0.0, norm<NormMax>(resC - refC), 1e-6) << C;
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test1)
{
    test<TypeParam>({{1,2},{3,4}}, {{1,2},{3,4}}, {{7,10},{15,22}});
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test2)
{
    test<TypeParam>({{1,2,3},{4,5,6}}, {{1,2},{3,4},{5,6}}, {{22,28},{49,64}});
}

TYPED_TEST_P(MatrixMatrixMultiplicationTest, Test3)
{
    test<TypeParam>({{1,2,3}}, {{1,2},{3,4},{5,6}}, {{22,28}});
}

REGISTER_TYPED_TEST_SUITE_P(MatrixMatrixMultiplicationTest, Test1, Test2, Test3);

typedef ::testing::Types<
    std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, Native>
    ,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, Native>
    ,std::tuple<Matrix<Sparse, double>, Matrix<Dense, double>, Matrix<Dense, double>, Native>
    ,std::tuple<Matrix<Dense, double>, Matrix<Sparse, double>, Matrix<Dense, double>, Native>
    ,std::tuple<Matrix<Sparse, double>, Matrix<Sparse, double>, Matrix<Sparse, double>, Native>
#ifdef WITH_INTELMKL
    ,std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, IntelMKL>
    ,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, IntelMKL>
    ,std::tuple<Matrix<Sparse, double>, Matrix<Dense, double>, Matrix<Dense, double>, IntelMKL>
    //,std::tuple<Matrix<Sparse, double>, Matrix<Sparse, double>, Matrix<Sparse, double>, IntelMKL>
#endif
#ifdef WITH_OPENBLAS
    ,std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, OpenBLAS>
    ,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, OpenBLAS>
#endif
#ifdef WITH_EIGEN
    ,std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, EigenI>
    ,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, EigenI>
#endif
    //,std::tuple<Matrix<Dense, double>, Matrix<Dense, double>, Matrix<Dense, double>, Blaze>
    //,std::tuple<Matrix<Dense, float>, Matrix<Dense, float>, Matrix<Dense, float>, Blaze>
> MyTypes;

INSTANTIATE_TYPED_TEST_SUITE_P(My, MatrixMatrixMultiplicationTest, MyTypes);
