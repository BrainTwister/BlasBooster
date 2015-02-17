// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/Threshold.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(Threshold,General)
{
	EXPECT_EQ(std::pow(2,-23),std::numeric_limits<float>::epsilon());
	EXPECT_EQ(std::pow(2,-52),std::numeric_limits<double>::epsilon());
	EXPECT_DOUBLE_EQ(0.2, 1 / std::sqrt(5) / std::sqrt(5));
}
