#include "BrainTwister/ArgumentParser.h"
#include "gtest/gtest.h"

TEST(ArgumentParserTest, Basic)
{
	char *argv[] = {strdup("program"), strdup("--input"), strdup("file"), strdup("arg1"), strdup("arg2")};
	int argc = (int)(sizeof(argv) / sizeof(argv[0]));

	BrainTwister::ArgumentParser arg(argc, argv, 2,
		{{"input", 'i', "Description of option input."},
		 {"verbose", "Print more output."}}
	);

	EXPECT_EQ(arg.getArgument(0), "arg1");
	EXPECT_EQ(arg.getArgument(1), "arg2");
	EXPECT_EQ(arg.getOptionValue("input"), "file");
	EXPECT_ANY_THROW(arg.getArgument(2));
}
