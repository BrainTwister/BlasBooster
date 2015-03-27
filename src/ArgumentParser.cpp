#include "BrainTwister/ArgumentParser.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace BrainTwister {
namespace ArgumentParser {

ArgumentParser::ArgumentParser(int argc, char* argv[], int nbArguments,
    std::vector<ArgumentDefinition> const& argumentDefinitions)
 : nbArguments_(nbArguments), argumentDefinitions_(argumentDefinitions)
{
	programName_ = argv[0];

	// Starting with index 1, because first entry is the name of the program
    for (int i = 1; i != argc; ++i)
    {
    	string current = argv[i];
    	if (current.compare(0, 2, "--") == 0)
    	{
    		// remove dashs
    		current.erase(0,2);

    		if (current == "help") {
    			printUsage();
    			exit(0);
    		}

    		bool found = false;
    		for (auto & option : argumentDefinitions_)
    		{
    			if (option.longLabel_ != current) continue;
    			string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw runtime_error(errorMessage);
    			string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw runtime_error(errorMessage);
    			option.value_ = nextString;
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw runtime_error("ArgumentParser: \"--" + current + "\" is not a valid option.");
    		}
    	} else if (current.compare(0, 1, "-") == 0) {

    		// remove dash
    		current.erase(0,1);
    		if (current.size() != 1) throw runtime_error("Short label has more than one letter.");

    		bool found = false;
    		for (auto & option : argumentDefinitions_)
    		{
    			if (option.shortLabel_ != current[0]) continue;
    			string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw runtime_error(errorMessage);
    			string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw runtime_error(errorMessage);
    			option.value_ = nextString;
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw runtime_error("ArgumentParser: \"-" + current + "\" is not a valid option.");
    		}

    	} else {
    		arguments_.push_back(current);
    	}
    }

	if (arguments_.size() != nbArguments)
	{
	    printUsage();
	    throw runtime_error("Wrong number of arguments.");
	}
}

void ArgumentParser::printUsage() const
{
	size_t maxWidth = 20;
	for (auto const& elem : argumentDefinitions_)
		if ( elem.longLabel_.size() > maxWidth ) maxWidth = elem.longLabel_.size();
	maxWidth += 2;

    cout << "\nUsage: " << programName_ << " <Options>\n" << endl;

    cout << "Options: " << endl;
    for (auto const& elem : argumentDefinitions_)
    	cout << "    " << left << setw(maxWidth) << elem.longLabel_ << elem.description_ << endl;
    cout << endl;
}

} // namespace ArgumentParser
} // namespace BrainTwister
