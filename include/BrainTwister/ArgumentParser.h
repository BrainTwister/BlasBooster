#ifndef ARGUMENTPARSER_H_
#define ARGUMENTPARSER_H_

#include <stdexcept>
#include <string>
#include <vector>

namespace BrainTwister {
namespace ArgumentParser {

enum ArgumentType {
	REQUIRED,
	OPTIONAL,
	BOOLEAN
};

/**
 * Analyze an argument list given for a command. Three types of arguments will be distinguished:
 *
 *   command [-boolean] [-optional \<string\>] \<nonOptional\>
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
		 : longLabel_(longLabel), shortLabel_(0), type_(BOOLEAN), description_(description)
		{}

		ArgumentDefinition(std::string const& longLabel, char shortLabel, std::string const& description)
		 : longLabel_(longLabel), shortLabel_(shortLabel), type_(BOOLEAN), description_(description)
		{}

		std::string longLabel_;
		char shortLabel_;
		ArgumentType type_;
		std::string description_;
		std::string value_;
	};

	ArgumentParser( int argc, char* argv[], int nbArguments,
		std::vector<ArgumentDefinition> const& argumentDefinitions = std::vector<ArgumentDefinition>()
	);

	std::string getArgument(int position) const
	{
		if (position >= nbArguments_) throw std::runtime_error("Argument position larger than given number of arguments.");
		return arguments_[position];
	}

	std::string getOptionValue(std::string const& longLabel) const
	{
		return "";
	}

	void printUsage() const;

private:

	// Store the first entry of argv
	std::string programName_;

	int nbArguments_;

	std::vector<ArgumentDefinition> argumentDefinitions_;

	std::vector<std::string> arguments_;

};

} // namespace ArgumentParser
} // namespace BrainTwister

#endif /* ARGUMENTPARSER_H_ */
