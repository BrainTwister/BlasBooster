// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_COREEXCEPTION_H_
#define BLASBOOSTER_CORE_COREEXCEPTION_H_

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

#endif // BLASBOOSTER_CORE_COREEXCEPTION_H_
