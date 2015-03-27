#include "BrainTwister/ArgumentParser.h"
#include "gtest/gtest.h"

namespace ap = BrainTwister::ArgumentParser;

TEST(ArgumentParserTest, Test1)
{
	char *argv[] = {strdup("program"), strdup("arg1"), strdup("arg2")};
	int argc = (int)(sizeof(argv) / sizeof(argv[0]));

	ap::ArgumentParser arg(argc, argv, 2,
		//{{"input", ap::value<int>(), "Description of option input."},
		{{"input", 'i', "Description of option input."},
		 {"verbose", "Print more output."}}
	);

	EXPECT_EQ(arg.getArgument(0), "arg1");
	EXPECT_EQ(arg.getArgument(1), "arg2");
	EXPECT_ANY_THROW(arg.getArgument(2));
}

//TEST(ArgumentParserTest, Test2)
//{
//	char *argv[] = {strdup("program"),strdup("-i"),strdup("optArg1"),strdup("arg1")};
//	int argc = (int)(sizeof(argv) / sizeof(argv[0]));
//
//	ArgumentParser ArgumentParser(argc,argv,
//		{{ "arg1", ArgumentParser::NonOptional, "Argument1" },
//		 { "i",    ArgumentParser::Optional,    "Argument2" }}
//	);
//
//	if ( ArgumentParser.getNonOptionalArgument("arg1") != "arg1" ) testSuite.errorLog("testArgumentParser: test 2 getNonOptionalArgument(arg1)");
//
//	try {
//		ArgumentParser.getNonOptionalArgument("arg2");
//		testSuite.errorLog("testArgumentParser: test 2 getNonOptionalArgument(arg2)");
//	} catch ( ... ) {}
//
//	if ( !ArgumentParser.isOptionalFlagSet("i") ) testSuite.errorLog("testArgumentParser: test 3 isOptionalFlagSet(\"i\")");
//	if ( ArgumentParser.isOptionalFlagSet("o") ) testSuite.errorLog("testArgumentParser: test 3 isOptionalFlagSet(\"o\")");
//	if ( ArgumentParser.getOptionalArgument("i") != "optArg1" ) testSuite.errorLog("testArgumentParser: test 2 getOptionalArgument(\"i\")");
//
//	try {
//		ArgumentParser.getOptionalArgument("o");
//		testSuite.errorLog("testArgumentParser: test 2 getOptionalArgument(o)");
//	} catch ( ... ) {}
//}
//
//TEST(ArgumentParserTest, Test3)
//{
//	char *argv[] = {strdup("program"),strdup("-i"),strdup("optArg1"),strdup("-bool1"),strdup("arg1")};
//	int argc = (int)(sizeof(argv) / sizeof(argv[0]));
//
//	ArgumentParser ArgumentParser(argc,argv,
//		{{ "arg1",  ArgumentParser::NonOptional, "Argument1" },
//		 { "i",     ArgumentParser::Optional,    "Argument2" },
//		 { "bool1", ArgumentParser::Boolean,     "Argument3" }}
//	);
//
//	if ( ArgumentParser.getNonOptionalArgument("arg1") != "arg1" ) testSuite.errorLog("testArgumentParser: test 3 getNonOptionalArgument(0)");
//
//	if ( !ArgumentParser.isOptionalFlagSet("i") ) testSuite.errorLog("testArgumentParser: test 3 isOptionalFlagSet(\"i\")");
//	if ( ArgumentParser.getOptionalArgument("i") != "optArg1" ) testSuite.errorLog("testArgumentParser: test 3 getOptionalArgument(\"i\")");
//
//	if ( !ArgumentParser.isBooleanFlagSet("bool1") ) testSuite.errorLog("testArgumentParser: test 3 isBooleanFlagSet(\"boolFlag1\")");
//	if ( ArgumentParser.isBooleanFlagSet("bool2") ) testSuite.errorLog("testArgumentParser: test 3 isBooleanFlagSet(\"boolFlag2\")");
//}
