// Copyright (C) 2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of ArgumentParser
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef ARGUMENTPARSER_H_
#define ARGUMENTPARSER_H_

#include <BrainTwister/ValueChecker.h>
#include <stdexcept>
#include <string>
#include <vector>

namespace BrainTwister {

/**
 * Analyze an argument list given for a command. Three types of arguments will be distinguished:
 *
 *   program [-boolean] [-optional \<string\>] \<nonOptional\>
 *
 *   - nonOptional: must be given in a defined order, position can be in front or behind optional/boolean arguments.
 *   - optional: can be given, but when one is given it must be directly followed by a string.
 *   - boolean: can be given and is not followed by a string. It's only switching an option on/off.
 *
 * Options can be with one or two leading dashes, generally one dash are used for single char options (-h) and
 * two dashes are used for others (--version).
 */
class ArgumentParser
{
public:

	struct ArgumentDefinition
	{
		ArgumentDefinition(std::string const& longLabel, std::string const& description)
		 : longLabel_(longLabel), shortLabel_(0), description_(description)
		{}

		ArgumentDefinition(std::string const& longLabel, char shortLabel, std::string const& description)
		 : longLabel_(longLabel), shortLabel_(shortLabel), description_(description)
		{}

		std::string longLabel_;
		char shortLabel_;
		std::string description_;
		std::string value_;
	};

	template <class ValueChecker>
	ArgumentParser(int argc, char* argv[], ValueChecker const& valueChecker,
		std::vector<ArgumentDefinition> const& argumentDefinitions = std::vector<ArgumentDefinition>());

	/// Return the number of arguments
	size_t size() const
	{
		return arguments_.size();
	}

	/// Return an argument at given position
	std::string get(size_t position) const
	{
		if (position >= arguments_.size()) throw std::runtime_error("Argument position larger than given number of arguments.");
		return arguments_[position];
	}

	/// Return an optional argument
	std::string get(std::string const& longLabel) const
	{
		for (auto & option : argumentDefinitions_)
			if (option.longLabel_ == longLabel) return option.value_;
		throw std::runtime_error("Option " + longLabel + " does not exist.");
	}

	void printUsage() const;

private:

	// Store the first entry of argv
	std::string programName_;

	std::vector<ArgumentDefinition> argumentDefinitions_;

	std::vector<std::string> arguments_;

};

template <class ValueChecker>
ArgumentParser::ArgumentParser(int argc, char* argv[], ValueChecker const& valueChecker,
    std::vector<ArgumentDefinition> const& argumentDefinitions)
 : argumentDefinitions_(argumentDefinitions)
{
	programName_ = argv[0];

	// Starting with index 1, because first entry is the name of the program
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
    		for (auto & option : argumentDefinitions_)
    		{
    			if (option.longLabel_ != current) continue;
    			std::string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw std::runtime_error(errorMessage);
    			std::string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw std::runtime_error(errorMessage);
    			option.value_ = nextString;
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw std::runtime_error("ArgumentParser: \"--" + current + "\" is not a valid option.");
    		}
    	} else if (current.compare(0, 1, "-") == 0) {

    		// remove dash
    		current.erase(0,1);
    		if (current.size() != 1) throw std::runtime_error("Short label has more than one letter.");

    		bool found = false;
    		for (auto & option : argumentDefinitions_)
    		{
    			if (option.shortLabel_ != current[0]) continue;
    			std::string errorMessage("ArgumentParser: no argument found for option \"-" + current + "\".");
    			if ( ++i >= argc ) throw std::runtime_error(errorMessage);
    			std::string nextString = argv[i];
    			if ( nextString[0] == '-' ) throw std::runtime_error(errorMessage);
    			option.value_ = nextString;
    			found = true;
    		}

    		if (!found) {
    		    printUsage();
    		    throw std::runtime_error("ArgumentParser: \"-" + current + "\" is not a valid option.");
    		}

    	} else {
    		arguments_.push_back(current);
    	}
    }

	if (!valueChecker(arguments_.size()))
	{
	    printUsage();
	    throw std::runtime_error("Wrong number of arguments.");
	}
}

} // namespace BrainTwister

#endif /* ARGUMENTPARSER_H_ */
