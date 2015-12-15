// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#include "BlasBooster/Utilities/Settings.h"
#include "gtest/gtest.h"

BLASBOOSTER_SETTINGS(Settings, \
    ((int, i1, 0)) \
	((double, d1, 0.0)) \
)

TEST(Settings, default)
{
	Settings settings;

	EXPECT_EQ(0, settings.i1);
	EXPECT_EQ(0.0, settings.d1);
}
