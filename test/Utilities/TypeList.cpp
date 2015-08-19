// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Utilities/TypeList.h"
#include "gtest/gtest.h"

using namespace BlasBooster;

TEST(TypeList, GetIndex)
{
	using MyList = TypeList<int, double, char>;

	EXPECT_EQ(0UL, (GetIndex<int,    MyList>::value));
	EXPECT_EQ(1UL, (GetIndex<double, MyList>::value));
	EXPECT_EQ(2UL, (GetIndex<char,   MyList>::value));
}
