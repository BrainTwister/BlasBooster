ArgumentParser
==============

Copyright 2015 BrainTwister - All rights reserved.

ArgumentParser is free software made available under the MIT License. For details see the LICENSE file.

Requirements
------------

- cmake (Version >= 2.6.6, http://www.cmake.org)
- gtest (Optional, but recommended, https://code.google.com/p/googletest)

Example
-------

```
#include "BrainTwister/ArgumentParser.h"

int main(int argc, char **argv)
{
    BrainTwister::ArgumentParser arg(argc, argv, 2,
        {{"input", 'i', "Description of option input."},
        {"verbose", "Print more output."}}
    );

    std::cout << "Argument 1:         " << arg.getArgument(0) << std::endl;
    std::cout << "Argument 2:         " << arg.getArgument(1) << std::endl;
    std::cout << "Value of '--input': " << arg.getOptionValue("input") << std::endl;
}
```
