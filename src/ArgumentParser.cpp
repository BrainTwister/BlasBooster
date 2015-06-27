#include "BrainTwister/ArgumentParser.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace BrainTwister {

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

} // namespace BrainTwister
