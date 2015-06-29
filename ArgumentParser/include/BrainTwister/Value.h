// Copyright (C) 2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of ArgumentParser
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef VALUE_H_
#define VALUE_H_

#include <string>

namespace BrainTwister {

struct ValueBase
{
    virtual ~ValueBase() {};

    virtual void setValue(std::string const& str) = 0;
};

template <class T>
struct Value : public ValueBase
{
    Value() : value() {}

    Value(T value) : value(value) {}

    virtual void setValue(std::string const& str) { value = str; }

    T value;
};

} // namespace BrainTwister

#endif /* VALUE_H_ */
