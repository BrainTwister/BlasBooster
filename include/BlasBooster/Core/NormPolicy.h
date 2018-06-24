#pragma once

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

} // namespace BlasBooster
