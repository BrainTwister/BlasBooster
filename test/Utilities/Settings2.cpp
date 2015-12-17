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

// Test arrays

BLASBOOSTER_SETTINGS(Settings2, \
	((std::vector<int>, v1, (std::vector<int>{5, -9}))) \
)

TEST(Settings2Test, default)
{
	Settings2 settings;

	EXPECT_EQ((std::vector<int>{5, -9}), settings.v1);
}

TEST(Settings2Test, parameter_constructor)
{
	Settings2 settings({8, 8, 2});

	EXPECT_EQ((std::vector<int>{8, 8, 2}), settings.v1);
}

TEST(Settings2Test, construct_by_json)
{
    std::stringstream ss("{\"v1\": [2, 2, 1]}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings2 settings(pt);

	EXPECT_EQ((std::vector<int>{2, 2, 1}), settings.v1);
}
