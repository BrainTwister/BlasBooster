#include "BrainTwister/ArgumentParser.h"
#include "gtest/gtest.h"

namespace bt = BrainTwister;

TEST(ArgumentParserTest, Basic)
{
    char *argv[] = {strdup("program"), strdup("--input"), strdup("file"), strdup("arg1"), strdup("arg2")};
    int argc = (int)(sizeof(argv) / sizeof(argv[0]));

    bt::ArgumentParser arg(argc, argv,
        {{"file1", bt::Value<std::string>(), "File 1."},
         {"file2", bt::Value<std::string>(), "File 2."}},
        {{"input", "i", bt::Value<std::string>(), "Description of the option input."},
         {"verbose", "v", bt::Value<std::string>("foo"), "Print more output."}}
    );

    EXPECT_EQ(arg.get<std::string>("file1"), "arg1");
    EXPECT_EQ(arg.get<std::string>("file2"), "arg2");
    EXPECT_EQ(arg.get<std::string>("input"), "file");
    EXPECT_EQ(arg.get<std::string>("verbose"), "foo");

}

