ArgumentParser
==============

Copyright 2015 BrainTwister - All rights reserved.

Requirements
------------

- cmake (Version >= 2.6.6, http://www.cmake.org)
- gtest (optional)

Usage
-----

#include "BrainTwister/ArgumentParser.h"

int main(int argc, char **argv)
{
    BrainTwister::ArgumentParser arg(argc, argv, 2,
        {{"input", 'i', "Description of option input."},
        {"verbose", "Print more output."}}
    );

    std::cout << arg.getArgument(0) << std::endl;
}

