#include "BrainTwister/ArgumentParser.h"
#include "gtest/gtest.h"

namespace bt = BrainTwister;

TEST(ArgumentParserTest, DISABLED_Basic)
{
//	char *argv[] = {strdup("program"), strdup("--input"), strdup("file"), strdup("arg1"), strdup("arg2")};
//	int argc = (int)(sizeof(argv) / sizeof(argv[0]));
//
//	bt::ArgumentParser arg(argc, argv, bt::Equal(2),
//		{{"input", 'i', bt::Value<std::string>(), "Description of option input."},
//		 {"verbose", bt::Value<bool>(), "Print more output."}}
//	);
//
//	EXPECT_EQ(arg.get(0), "arg1");
//	EXPECT_EQ(arg.get(1), "arg2");
//	EXPECT_ANY_THROW(arg.get(2));
//	EXPECT_EQ(arg.get("input"), "file");
}
