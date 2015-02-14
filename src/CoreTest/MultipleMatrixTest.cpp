#include "CoreLib/AllMatrixTypes.h"
#include "CoreLib/BinaryFunctors.h"
#include "CoreLib/Multiplication.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

class MultipleMatrixTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    	M1.resize(3,3,ContinuousNumberFiller());

    	std::shared_ptr<Matrix<Sparse,double> > ptrM1(new Matrix<Sparse,double>(3,3,0,ContinuousNumberFiller()));
    	std::shared_ptr<Matrix<Sparse,float> > ptrM2(new Matrix<Sparse,float>(3,3,0,ContinuousNumberFiller()));

    	M2.reset(ptrM1,ptrM2);
    }

	Matrix<Dense,double> M1;
	MultipleMatrix< Matrix<Sparse,double>, Matrix<Sparse,float> > M2;
};

TEST_F(MultipleMatrixTest,Addition)
{
	auto M3 = M1 + M2;
	auto M4 = M1 + M1 + M1;

	EXPECT_TRUE(M3.equal(M4)) << "Matrix<Dense,double> + MultipleMatrix< Matrix<Sparse,double>, Matrix<Sparse,float> >";
}

TEST_F(MultipleMatrixTest,Multiplication)
{
	auto M3 = M1 * M2;
	auto M4 = M1 * (M1 + M1);

	EXPECT_TRUE(M3.equal(M4)) << "Matrix<Dense,double> * MultipleMatrix< Matrix<Sparse,double>, Matrix<Sparse,float> >";
}

TEST_F(MultipleMatrixTest,Norm)
{
	EXPECT_DOUBLE_EQ(norm<NormTwo>(M1),norm<NormTwo>(M2));
}
