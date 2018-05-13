#pragma once

#include <cassert>
#include <stdexcept>
#include <string>

struct CoreException : public std::runtime_error
{
    CoreException(std::string const& msg) : std::runtime_error(msg) {}
};

#if defined(BLASBOOSTER_CORE_FAILURE_TO_EXCEPTION)
    #define BLASBOOSTER_CORE_FAILURE(msg) throw CoreException(msg);
#else
    #define BLASBOOSTER_CORE_FAILURE(msg) assert(false && msg);
#endif
