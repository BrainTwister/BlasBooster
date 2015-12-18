// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Utilities/Settings.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "gtest/gtest.h"
#include <iostream>
#include <vector>

// Test nested structures

BLASBOOSTER_SETTINGS(A, \
    ((int, i, 0)) \
	((double, d, 0.0)) \
)

BLASBOOSTER_SETTINGS(B, \
	((int, i, 0)) \
	((A, a, A())) \
)

BLASBOOSTER_SETTINGS(C, \
	((std::vector<A>, v, std::vector<A>())) \
)

TEST(Settings3Test, B_default)
{
	B b;

	EXPECT_EQ(0, b.i);
	EXPECT_EQ(A(), b.a);
}

TEST(Settings3Test, B_construct_by_json)
{
    std::stringstream ss("{\"i\": 42, \"a\": {\"i\": 33, \"d\": 3.8}}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    B b(pt);

	EXPECT_EQ(42, b.i);
	EXPECT_EQ((A(33, 3.8)), b.a);
}

TEST(Settings3Test, C_default)
{
	C c;

	EXPECT_EQ(std::vector<A>(), c.v);
}
