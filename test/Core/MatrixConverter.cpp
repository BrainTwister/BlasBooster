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
		threshold = Threshold(ThresholdSettings()
    	    .set_significanceThresholdSinglePrecision(1e-5)
		    .set_significanceThresholdDoublePrecision(1e-10)
		    .set_occupationThresholdMatrixZeroSinglePrecision(0.0)
		    .set_occupationThresholdMatrixZeroDoublePrecision(0.0)
		    .set_occupationThresholdMatrixSparseFloatSinglePrecision(0.0)
		    .set_occupationThresholdMatrixSparseFloatDoublePrecision(0.5)
		    .set_occupationThresholdMatrixDenseFloatSinglePrecision(0.0)
		    .set_occupationThresholdMatrixDenseFloatDoublePrecision(1.0)
		    .set_occupationThresholdMatrixSparseDoubleSinglePrecision(0.5)
		    .set_occupationThresholdMatrixSparseDoubleDoublePrecision(0.5)
		    .set_occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision(0.5)
		    .set_occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision(1.0)
		    .set_occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision(0.5)
		    .set_occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision(1.0)
		    .set_occupationThresholdMatrixDenseDoubleSinglePrecision(1.0)
		    .set_occupationThresholdMatrixDenseDoubleDoublePrecision(1.0)
		);
    }

	Threshold threshold;
};

TEST_F(MatrixConverterTest, ConvertDenseToSparse)
{
	Matrix<Dense,double> A {
		{ 1e-12, 1e-6  },
		{ 1e-6 , 1e-12 }
	};

	EXPECT_DOUBLE_EQ(1e-10, threshold.getSignificanceThreshold<double>());

	EXPECT_DOUBLE_EQ(0.5, A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<double>())));
	EXPECT_DOUBLE_EQ(0.0, A.getOccupation(AbsoluteValueRangeChecker<ThresholdType>(threshold.getSignificanceThreshold<float>())));

	auto B = MatrixConverter()(A,threshold);

	size_t typeIndex = Matrix<Sparse,float>::typeIndex_;
	EXPECT_EQ(typeIndex, B->getTypeIndex());

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
