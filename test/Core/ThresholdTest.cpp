#include "BlasBooster/Core/Threshold.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(Threshold, General)
{
	EXPECT_EQ(std::pow(2,-23),std::numeric_limits<float>::epsilon());
	EXPECT_EQ(std::pow(2,-52),std::numeric_limits<double>::epsilon());
	EXPECT_DOUBLE_EQ(0.2, 1 / std::sqrt(5) / std::sqrt(5));
}
