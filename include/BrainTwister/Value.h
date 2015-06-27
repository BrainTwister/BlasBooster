// Copyright (C) 2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of ArgumentParser
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef VALUE_H_
#define VALUE_H_

namespace BrainTwister {

struct ValueBase
{
    virtual ~ValueBase() {};
};

template <class T>
struct Value : public ValueBase
{
    Value(T value) : value(value) {}

    T value;
};
template <class T>

} // namespace BrainTwister

#endif /* VALUE_H_ */
