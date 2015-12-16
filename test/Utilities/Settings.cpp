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
#include "gtest/gtest.h"
#include <iostream>

BLASBOOSTER_SETTINGS(Settings, \
    ((int, i1, 0)) \
	((double, d1, 0.0)) \
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
