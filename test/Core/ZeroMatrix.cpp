#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/ZeroMatrix.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(ZeroMatrix, convert_from_dense)
{
	Matrix<Dense,double> A{{1.0, 2.0}, {3.0, 4.0}};
	Matrix<Dense,double> DZ{2, 2, AllFiller<double>{0.0}};
    Matrix<Zero> Z{A};

	EXPECT_EQ(2UL, Z.getNbRows());
	EXPECT_EQ(2UL, Z.getNbColumns());
	EXPECT_EQ(4UL, Z.getSize());

	EXPECT_EQ(2UL, Z.getNbRows());

	Matrix<Dense,double> D{Z};

	EXPECT_EQ(2UL, D.getNbRows());
	EXPECT_EQ(2UL, D.getNbColumns());
	EXPECT_EQ(4UL, D.getSize());
	EXPECT_TRUE(D.equal(DZ));
}

TEST(ZeroMatrix, addition)
{
	Matrix<Dense,double> A{{1.0, 2.0}, {3.0, 4.0}};
	Matrix<Zero> Z{2, 2};

	EXPECT_TRUE(A.equal(A + Z));
	EXPECT_TRUE(A.equal(Z + A));
	EXPECT_TRUE(Z.equal(Z + Z));
}

TEST(ZeroMatrix, multiplication)
{
	Matrix<Dense,double> A{{1.0, 2.0}, {3.0, 4.0}};
	Matrix<Zero> Z{2, 2};

	auto&& AZ = (A * Z).execute<Native>();
	EXPECT_TRUE(Z.equal(AZ));

	auto&& ZA = (Z * A).execute<Native>();
	EXPECT_TRUE(Z.equal(ZA));

	auto&& ZZ = (Z * Z).execute<Native>();
	EXPECT_TRUE(Z.equal(ZZ));
}
