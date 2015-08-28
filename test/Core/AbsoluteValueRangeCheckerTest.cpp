// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Core/AbsoluteValueRangeChecker.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(AbsoluteValueRangeCheckerTest,Exceptions)
{
	EXPECT_THROW(AbsoluteValueRangeChecker<double>(-1.0),CoreException);
	EXPECT_NO_THROW(AbsoluteValueRangeChecker<double>(1.0));

	EXPECT_NO_THROW((AbsoluteValueRangeChecker<double,InclusiveBound,InclusiveBound>(1.0,1.0)));
	EXPECT_THROW((AbsoluteValueRangeChecker<double,InclusiveBound,InclusiveBound>(1.0,0.5)),CoreException);

	EXPECT_THROW((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1.0,1.0)),CoreException);
	EXPECT_THROW((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1.0,0.5)),CoreException);

	EXPECT_THROW((AbsoluteValueRangeChecker<double,ExclusiveBound,ExclusiveBound>(1.0,1.0)),CoreException);
	EXPECT_THROW((AbsoluteValueRangeChecker<double,ExclusiveBound,ExclusiveBound>(1.0,0.5)),CoreException);
}

TEST(AbsoluteValueRangeCheckerTest,General)
{
	EXPECT_FALSE(AbsoluteValueRangeChecker<double>(1e-6)(1e-7));
	EXPECT_FALSE(AbsoluteValueRangeChecker<double>(1e-6)(1e-6));
	EXPECT_TRUE(AbsoluteValueRangeChecker<double>(1e-6)(1e-5));

	EXPECT_FALSE(AbsoluteValueRangeChecker<double>(1e-6)(-1e-7));
	EXPECT_FALSE(AbsoluteValueRangeChecker<double>(1e-6)(-1e-6));
	EXPECT_TRUE(AbsoluteValueRangeChecker<double>(1e-6)(-1e-5));

	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(1e-20)));
	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(1e-16)));
	EXPECT_TRUE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(1e-10)));
	EXPECT_TRUE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(1e-8)));
	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(1e-7)));

	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(-1e-20)));
	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(-1e-16)));
	EXPECT_TRUE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(-1e-10)));
	EXPECT_TRUE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(-1e-8)));
	EXPECT_FALSE((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1e-16,1e-8)(-1e-7)));
}

TEST(AbsoluteValueRangeCheckerTest,Polymorphism)
{
	EXPECT_EQ((AbsoluteValueRangeChecker<double>::id_),0UL);
	EXPECT_EQ((AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>::id_),1UL);
	EXPECT_EQ((AbsoluteValueRangeChecker<double,InclusiveBound,InclusiveBound>::id_),2UL);
	EXPECT_EQ((AbsoluteValueRangeChecker<double,ExclusiveBound,ExclusiveBound>::id_),3UL);

	std::shared_ptr<ValueCheckerBase> ptrV1(new AbsoluteValueRangeChecker<double>(1.0));
	std::shared_ptr<ValueCheckerBase> ptrV2(new AbsoluteValueRangeChecker<double>(2.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV1,ptrV2));
	EXPECT_FALSE(ValueCheckerLess()(ptrV2,ptrV1));

	std::shared_ptr<ValueCheckerBase> ptrV3(new AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1.0,2.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV1,ptrV3));
	EXPECT_FALSE(ValueCheckerLess()(ptrV3,ptrV1));

	std::shared_ptr<ValueCheckerBase> ptrV4(new AbsoluteValueRangeChecker<double,ExclusiveBound,InclusiveBound>(1.0,3.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV3,ptrV4));
	EXPECT_FALSE(ValueCheckerLess()(ptrV4,ptrV3));

	std::shared_ptr<ValueCheckerBase> ptrV5(new AbsoluteValueRangeChecker<double,InclusiveBound,InclusiveBound>(1.0,2.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV1,ptrV5));
	EXPECT_FALSE(ValueCheckerLess()(ptrV5,ptrV1));

	std::shared_ptr<ValueCheckerBase> ptrV6(new AbsoluteValueRangeChecker<double,InclusiveBound,InclusiveBound>(1.0,3.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV5,ptrV6));
	EXPECT_FALSE(ValueCheckerLess()(ptrV6,ptrV5));

	std::shared_ptr<ValueCheckerBase> ptrV7(new AbsoluteValueRangeChecker<double,ExclusiveBound,ExclusiveBound>(1.0,2.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV1,ptrV7));
	EXPECT_FALSE(ValueCheckerLess()(ptrV7,ptrV1));

	std::shared_ptr<ValueCheckerBase> ptrV8(new AbsoluteValueRangeChecker<double,ExclusiveBound,ExclusiveBound>(1.0,3.0));

	EXPECT_TRUE(ValueCheckerLess()(ptrV7,ptrV8));
	EXPECT_FALSE(ValueCheckerLess()(ptrV8,ptrV7));
}
