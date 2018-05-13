#pragma once

#include <iostream>

namespace BlasBooster {

#ifdef BLASBOOSTER_DEBUG_MODE
    #define BLASBOOSTER_DEBUG_PRINT(message)\
        std::cout << message << std::endl;
#else
    #define BLASBOOSTER_DEBUG_PRINT(message)
#endif

} // namespace BlasBooster
