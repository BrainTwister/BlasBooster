#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Core/Multiplication.h"
#include "BlasBooster/Core/Threshold.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(SparseMatrix,SparseDoubleNorm)
{
	Matrix<Dense,double> A(5,5,DiagonalFiller());
	Matrix<Sparse,double> spA(A);

	EXPECT_DOUBLE_EQ(sqrt(5.0),spA.getNorm());
	EXPECT_DOUBLE_EQ(0.2,spA.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(1.0e-10)));
}

TEST(SparseMatrix,SparseFloatNorm)
{
	Matrix<Dense,float> A(5,5,DiagonalFiller());
	Matrix<Sparse,float> spA(A);

	EXPECT_FLOAT_EQ(sqrt(5.0),spA.getNorm());
	EXPECT_FLOAT_EQ(0.2,spA.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(1.0e-10)));
}

TEST(SparseMatrix,DenseSparseConversion)
{
	Matrix<Dense,double> A {{0.0,2.0},{3.0,0.0}};
	Matrix<Sparse,double> B(A);
	Matrix<Dense,double> C(B);

	EXPECT_TRUE(C.equal(A));
}

#if 0

TEST(SparseMatrix,)
{
	Matrix<Dense,double> A {{0.0,2.0},{5.0,0.0}};
	Matrix<Dense,double> B {{3.0,4.0},{7.0,8.0}};
	auto C = A * B;

	Matrix<Sparse,double> spA(A);
	Matrix<Sparse,double> spB(B);
	Matrix<Sparse,double> spC = spA * spB;

	Matrix<Dense,double> checkC(spC);
	EXPECT_TRUE(C.equal(checkC));
}

TEST(SparseMatrix,)
{
	Matrix<Dense,double> A {{0.0,2.0},{5.0,0.0}};
	Matrix<Dense,double> B {{3.0,4.0},{7.0,8.0}};
	Matrix<Dense,double> C = A * B;

	Matrix<Sparse,double> spA(A);
	Matrix<Sparse,double> spB(B);
	Matrix<Sparse,double> spC(spA.getNbRows(),spB.getNbColumns());

	MultiplicationFunctor<Sparse,double,Parameter<>,Sparse,double,Parameter<>,Sparse,double,Parameter<> >()(spA,spB,spC);

	Matrix<Dense,double> checkC(spC);
	if ( C.notEqual(checkC) ) testSuite.errorLog("testSparseMatrix: test mult(sparse,sparse)");
}

TEST(SparseMatrix,)
{
	Matrix<Dense,double> A {{0.0,2.0},{5.0,0.0}};
	Matrix<Dense,double> B {{3.0,4.0},{7.0,8.0}};

	Matrix<Sparse,double> spA(A);
	Matrix<Dense,double> C1 = A * B;
	Matrix<Dense,double> C2 = spA * B;

	if ( C1.notEqual(C2) ) testSuite.errorLog("testSparseMatrix: test mult(sparse,dense)");
}

TEST(SparseMatrix,)
{
	Matrix<Dense,double> A {{3.0,4.0},{7.0,8.0}};
	Matrix<Dense,double> B {{0.0,2.0},{5.0,0.0}};

	Matrix<Sparse,double> spB(B);
	Matrix<Dense,double> C1 = A * B;
	Matrix<Dense,double> C2 = A * spB;

	if ( C1.notEqual(C2) ) testSuite.errorLog("testSparseMatrix: test mult(dense,sparse)");
}

TEST(SparseMatrix,)
{
	const Matrix<Dense,double> refA {{3.0,4.0},{7.0,8.0}};
	const Matrix<Dense,double> refB {{0.0,2.0},{5.0,0.0}};

	auto refC = refA + refB;
	auto refD = refA - refB;

	const Matrix<Sparse,double> A(refA);
	const Matrix<Sparse,double> B(refB);

	auto C = A + B;
	auto D = A - B;

	if (Matrix<Dense,double>(C).notEqual(refC)) testSuite.errorLog("testSparseMatrix: test <Sparse,double> + <Sparse,double>");
	if (Matrix<Dense,double>(D).notEqual(refD)) testSuite.errorLog("testSparseMatrix: test <Sparse,double> - <Sparse,double>");

	auto E = refA + B;
	auto F = refA - B;

	if (Matrix<Dense,double>(E).notEqual(refC)) testSuite.errorLog("testSparseMatrix: test <Dense,double> + <Sparse,double>");
	if (Matrix<Dense,double>(F).notEqual(refD)) testSuite.errorLog("testSparseMatrix: test <Dense,double> - <Sparse,double>");
}
#endif
