// Copyright (C) 2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of ArgumentParser
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef VALUECHECKER_H_
#define VALUECHECKER_H_

namespace BrainTwister {

struct Arbitrary
{
    bool operator () (int value) const
    {
        return true;
    }
};

struct Equal
{
    Equal(int reference)
     : reference_(reference)
    {}

    bool operator () (int value) const
    {
        return value == reference_;
    }

    int reference_;
};

struct LargerThan
{
    LargerThan(int reference)
     : reference_(reference)
    {}

    bool operator () (int value) const
    {
        return value > reference_;
    }

    int reference_;
};

} // namespace BrainTwister

#endif /* VALUECHECKER_H_ */
