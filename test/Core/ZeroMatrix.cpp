#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/ZeroMatrix.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(ZeroMatrix, convert_from_dense)
{
	Matrix<Dense,double> A{{1.0, 2.0}, {3.0, 4.0}};
	Matrix<Dense,double> DZ{2, 2, AllFiller{0.0}};
    Matrix<Zero,double> Z{A};

	EXPECT_EQ(2UL, Z.getNbRows());

	Matrix<Dense,double> D{Z};

	EXPECT_EQ(2UL, D.getNbRows());
	EXPECT_EQ(2UL, D.getNbColumns());
	EXPECT_EQ(4UL, D.getSize());
	EXPECT_TRUE(D.equal(DZ));
}
