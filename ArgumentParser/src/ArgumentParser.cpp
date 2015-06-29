#include "BrainTwister/ArgumentParser.h"
#include <iomanip>
#include <iostream>

namespace BrainTwister {

ArgumentParser::ArgumentParser(int argc, char* argv[],
	std::vector<RequiredArgumentDefinition> const& reqArgDefs,
	std::vector<OptionalArgumentDefinition> const& optArgDefs)
 : programName(argv[0]),
   reqArgDefs(reqArgDefs),
   optArgDefs(optArgDefs)
{
	// Starting with index 1, because first entry is the name of the program
	size_t nbRegArgs = 0;
    for (int i = 1; i != argc; ++i)
    {
    	std::string current = argv[i];
    	if (current.compare(0, 2, "--") == 0)
    	{
    		// remove dashs
    		current.erase(0,2);

    		if (current == "help") {
    			printUsage();
    			exit(0);
    		}

    		bool found = false;
    		for (auto & option : optArgDefs)
    		{
    			if (option.label != current) continue;
    			std::string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw std::runtime_error(errorMessage);
    			std::string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw std::runtime_error(errorMessage);
    			option.value->setValue(nextString);
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw std::runtime_error("ArgumentParser: \"--" + current + "\" is not a valid option.");
    		}
    	} else if (current.compare(0, 1, "-") == 0) {

    		// remove dash
    		current.erase(0,1);

    		if (current == "h") {
    			printUsage();
    			exit(0);
    		}

    		if (current.size() != 1) throw std::runtime_error("Short label has more than one letter.");

    		bool found = false;
    		for (auto & option : optArgDefs)
    		{
    			if (option.shortLabel != current) continue;
    			std::string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw std::runtime_error(errorMessage);
    			std::string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw std::runtime_error(errorMessage);
    			option.value->setValue(nextString);
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw std::runtime_error("ArgumentParser: \"-" + current + "\" is not a valid option.");
    		}

    	} else {
    		reqArgDefs[nbRegArgs++].value->setValue(current);
    	}
    }
}

void ArgumentParser::printUsage() const
{
	size_t maxWidth = 20;
	for (auto const& elem : optArgDefs)
		if ( elem.label.size() > maxWidth ) maxWidth = elem.label.size();
	maxWidth += 2;

    std::cout << "\nUsage: " << programName << " <Options>\n" << std::endl;

    std::cout << "Options: " << std::endl;
    for (auto const& elem : optArgDefs)
    	std::cout << "    " << std::left << std::setw(maxWidth) << elem.label << elem.description << std::endl;
    std::cout << std::endl;
}

} // namespace BrainTwister
