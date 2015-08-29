// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_NORMPOLICY_H_
#define BLASBOOSTER_CORE_NORMPOLICY_H_

#include "Norm.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace BlasBooster {

template <class Derived, class NormType>
class NormPolicy
{
public:

    NormPolicy()
     : norm_(0.0), isNormUpToDate_(false)
    {}

    double getNorm() const
    {
        if (!isNormUpToDate_) updateNorm();
        return norm_;
    }

    bool isNormLargerThan(double value) const
    {
        if (!isNormUpToDate_) updateNorm();
        return norm_ > value;
    }

    bool isNormSmallerThan(double value) const
    {
        if (!isNormUpToDate_) updateNorm();
        return norm_ < value;
    }

    bool isNormUpToDate() const { return isNormUpToDate_; };

    void updateNorm() const
    {
        if (!isNormUpToDate_) {
            norm_ = norm<NormType>(*(static_cast<const Derived*>(this)));
            isNormUpToDate_ = true;
        }
    }

private:

    mutable double norm_;

    mutable bool isNormUpToDate_;

};

template <class P, class NormType>
class NormPolicy<Matrix<Zero,NoType,P>,NormType>
{
public:

    double getNorm() const
    {
        return 0.0;
    }

    bool isNormLargerThan(double value) const
    {
        return 0.0 > value;
    }

    bool isNormSmallerThan(double value) const
    {
        return 0.0 < value;
    }
};

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_NORMPOLICY_H_
