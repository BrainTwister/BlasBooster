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

// Test pointer

BLASBOOSTER_SETTINGS(Settings4, \
	((std::shared_ptr<int>, ptr_i, std::shared_ptr<int>())) \
)

TEST(Settings4Test, default)
{
	Settings4 settings;

	EXPECT_EQ(std::shared_ptr<int>(), settings.ptr_i);
}

TEST(Settings4Test, parameter_constructor)
{
	std::shared_ptr<int> ptr_i{new int{4}};
	Settings4 settings(ptr_i);

	EXPECT_EQ(4, *settings.ptr_i);
}

TEST(Settings4Test, construct_by_json)
{
    std::stringstream ss("{\"ptr_i\": 4}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings4 settings(pt);

	EXPECT_EQ(4, *settings.ptr_i);
}
