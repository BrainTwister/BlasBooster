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

BLASBOOSTER_SETTINGS(Settings, \
    ((int, i1, 0)) \
	((double, d1, 0.0)) \
)

BLASBOOSTER_SETTINGS(Settings3, \
	((int, i1, 0)) \
	((Settings, s1, Settings())) \
)

TEST(Settings3Test, default)
{
	Settings3 settings;

	EXPECT_EQ(0, settings.i1);
	EXPECT_EQ(Settings(), settings.s1);
}

TEST(Settings3Test, construct_by_json)
{
    std::stringstream ss("{\"i1\": 42, \"s1\": {\"i1\": 33, \"d1\": 3.8}}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings3 settings(pt);

	EXPECT_EQ(42, settings.i1);
	EXPECT_EQ((Settings(33, 3.8)), settings.s1);
}
