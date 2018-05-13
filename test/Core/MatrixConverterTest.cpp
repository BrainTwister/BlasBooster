#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Core/MatrixConverter.h"
#include "BlasBooster/Core/MatrixIO.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

class MatrixConverterTest : public ::testing::Test
{
public:

	virtual ~MatrixConverterTest() {}

protected:

    virtual void SetUp()
    {
    	threshold = Threshold(ThresholdSettings(
			1e-5, // significanceThresholdFloatPrecision
			1e-10, // significanceThresholdDoublePrecision
			0.0,  // occupationThresholdMatrixSparseFloatSinglePrecision
			0.5,  // occupationThresholdMatrixSparseFloatDoublePrecision
			0.0,  // occupationThresholdMatrixDenseFloatSinglePrecision
			1.0,  // occupationThresholdMatrixDenseFloatDoublePrecision
			0.5,  // occupationThresholdMatrixSparseDoubleSinglePrecision
			0.5,  // occupationThresholdMatrixSparseDoubleDoublePrecision
			0.5,  // occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision
			1.0,  // occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision
			0.5,  // occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision
			1.0,  // occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision
			1.0,  // occupationThresholdMatrixDenseDoubleSinglePrecision
			1.0   // occupationThresholdMatrixDenseDoubleDoublePrecision
		));
    }

	Threshold threshold;
};

TEST_F(MatrixConverterTest, ConvertDenseToSparse)
{
	Matrix<Dense,double> A {
		{ 1e-12, 1e-6  },
		{ 1e-6 , 1e-12 }
	};

	EXPECT_DOUBLE_EQ(0.5,A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>())));
	EXPECT_DOUBLE_EQ(0.0,A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<float>())));

	auto B = MatrixConverter()(A,threshold);

	size_t typeIndex = Matrix<Sparse,float>::typeIndex_;
	EXPECT_EQ(typeIndex,B->getTypeIndex());

	Matrix<Dense,double> C {
		{ 0.0 , 1e-6 },
		{ 1e-6, 0.0  }
	};

	EXPECT_TRUE(C.equal(Matrix<Dense,double>(B)));
}

TEST_F(MatrixConverterTest, ConvertDenseDoubleToDenseFloat)
{
	Matrix<Dense,double> A {
		{ 1e-6, 1e-6 },
		{ 1e-6, 1e-6 }
	};

	EXPECT_DOUBLE_EQ(1e-5,threshold.getSignificanceThreshold<float>());

	EXPECT_DOUBLE_EQ(1.0,A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>())));
	EXPECT_DOUBLE_EQ(0.0,A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<float>())));

	EXPECT_LE((A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<float>()))),
		(threshold.getOccupationThreshold<Matrix<Dense,float>,float>()));

	EXPECT_LE((A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>()))),
	    (threshold.getOccupationThreshold<Matrix<Dense,float>,double>()));

	EXPECT_TRUE((IsConvertible< MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> > >()(A,threshold)));
	EXPECT_TRUE((IsConvertible< Matrix<Dense,float> >()(A,threshold)));

	auto B = MatrixConverter()(A,threshold);

	size_t typeIndex = Matrix<Dense,float>::typeIndex_;
	EXPECT_EQ(typeIndex,B->getTypeIndex());

	Matrix<Dense,double> C {
		{ 1e-6, 1e-6 },
		{ 1e-6, 1e-6 }
	};

	EXPECT_TRUE(C.equal(Matrix<Dense,double>(B)));
}
