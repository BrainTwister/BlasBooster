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

BLASBOOSTER_SETTINGS(Settings, \
    ((int, i1, 0)) \
	((double, d1, 0.0)) \
)

BLASBOOSTER_SETTINGS(Settings2, \
	((int, i1, 0)) \
	((std::vector<int>, v1, std::vector<int>())) \
)

BLASBOOSTER_SETTINGS(Settings3, \
	((int, i1, 0)) \
	((Settings, s1, Settings())) \
)

BLASBOOSTER_SETTINGS(Settings4, \
	((std::shared_ptr<int>, ptr_i, std::shared_ptr<int>())) \
)

TEST(SettingsTest, default)
{
	Settings settings;

	EXPECT_EQ(0, settings.i1);
	EXPECT_EQ(0.0, settings.d1);
	EXPECT_TRUE(Settings::IsSetting);
}

TEST(SettingsTest, parameter_construction)
{
	Settings settings(42, 2.3);

	EXPECT_EQ(42, settings.i1);
	EXPECT_EQ(2.3, settings.d1);
}

TEST(SettingsTest, copy_construction)
{
	Settings s1(42, 2.3);
	Settings s2(s1);

	EXPECT_EQ(42, s2.i1);
	EXPECT_EQ(2.3, s2.d1);
}

TEST(SettingsTest, ptree_construction)
{
	boost::property_tree::ptree pt;
	pt.put("i1", "42");
	pt.put("d1", "2.3");
	Settings settings(pt);

	EXPECT_EQ(42, settings.i1);
	EXPECT_EQ(2.3, settings.d1);
}

TEST(SettingsTest, compare)
{
	Settings s1(42, 2.3);
	Settings s2(s1);
	Settings s3;

	EXPECT_EQ(s1, s2);
	EXPECT_NE(s1, s3);
}

TEST(SettingsTest, serialization)
{
	Settings s1(42, 2.3);
    std::stringstream ss;
    boost::archive::binary_oarchive oar(ss);
    oar << s1;

	Settings s2;
    boost::archive::binary_iarchive iar(ss);
    iar >> s2;

	EXPECT_EQ(s1, s2);
}

TEST(Settings2Test, default)
{
	Settings2 settings;

	EXPECT_EQ(0, settings.i1);
	EXPECT_TRUE(settings.v1.empty());
}

TEST(Settings2Test, parameter_constructor)
{
	Settings2 settings(37, {8, 8, 2});

	EXPECT_EQ(37, settings.i1);
	EXPECT_EQ((std::vector<int>{8, 8, 2}), settings.v1);
}

TEST(Settings2Test, construct_by_json)
{
    std::stringstream ss("{\"i1\": 42, \"v1\": [2, 2, 1]}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings2 settings(pt);

	EXPECT_EQ(42, settings.i1);
	EXPECT_EQ((std::vector<int>{2, 2, 1}), settings.v1);
}

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
