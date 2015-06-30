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
    bt::ArgumentParser arg(argc, argv,
        {{"file1", bt::Value<std::string>(), "File 1."},
         {"file2", bt::Value<std::string>(), "File 2."}},
        {{"input", "i", bt::Value<std::string>(), "Description of the option input."},
         {"verbose", "v", bt::Value<std::string>("foo"), "Print more output."}}
    );

    std::cout << "Argument 1:                  " << arg.get<std::string>("file1") << std::endl;
    std::cout << "Argument 2:                  " << arg.get<std::string>("file2") << std::endl;
    std::cout << "Value of option \"input\":   " << arg.get<std::string>("input") << std::endl;
    std::cout << "Value of option \"verbose\": " << arg.get<std::string>("verbose") << std::endl;
}
```

