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
#include <string>

// Test simple types

BLASBOOSTER_SETTINGS(Settings, \
    ((int, i, 0)) \
	((double, d, 0.0)) \
	((std::string, s, "foo")) \
)

TEST(Settings1Test, default)
{
	Settings settings;

	EXPECT_EQ(0, settings.i);
	EXPECT_EQ(0.0, settings.d);
	EXPECT_EQ("foo", settings.s);
	EXPECT_TRUE(BlasBooster::SettingsDetails::is_setting<Settings>::value);
}

TEST(Settings1Test, parameter_construction)
{
	Settings settings(42, 2.3);

	EXPECT_EQ(42, settings.i);
	EXPECT_EQ(2.3, settings.d);
}

TEST(Settings1Test, copy_construction)
{
	Settings s1(42, 2.3);
	Settings s2(s1);

	EXPECT_EQ(42, s2.i);
	EXPECT_EQ(2.3, s2.d);
}

TEST(Settings1Test, ptree_construction)
{
	boost::property_tree::ptree pt;
	pt.put("i", "42");
	pt.put("d", "2.3");
	Settings settings(pt);

	EXPECT_EQ(42, settings.i);
	EXPECT_EQ(2.3, settings.d);
}

TEST(Settings1Test, construct_by_json)
{
    std::stringstream ss("{\"i\": 42, \"d\": 3.8, \"s\": \"bar\"}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings settings(pt);

	EXPECT_EQ(42, settings.i);
	EXPECT_EQ(3.8, settings.d);
	EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, construct_by_json_unordered)
{
    std::stringstream ss("{\"s\": \"bar\", \"i\": 42, \"d\": 3.8}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings settings(pt);

	EXPECT_EQ(42, settings.i);
	EXPECT_EQ(3.8, settings.d);
	EXPECT_EQ("bar", settings.s);
}

TEST(Settings1Test, construct_by_json_with_default)
{
    std::stringstream ss("{\"i\": 42}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings settings(pt);

	EXPECT_EQ(42, settings.i);
	EXPECT_EQ(0.0, settings.d);
	EXPECT_EQ("foo", settings.s);
}

TEST(Settings1Test, compare)
{
	Settings s1(42, 2.3);
	Settings s2(s1);
	Settings s3;

	EXPECT_EQ(s1, s2);
	EXPECT_NE(s1, s3);
}

//TEST(Settings1Test, serialization)
//{
//	Settings s1(42, 2.3);
//    std::stringstream ss;
//    boost::archive::binary_oarchive oar(ss);
//    oar << s1;
//
//	Settings s2;
//    boost::archive::binary_iarchive iar(ss);
//    iar >> s2;
//
//	EXPECT_EQ(s1, s2);
//}
