#pragma once

#include "AbsoluteValueRangeChecker.h"
#include "Occupation.h"
#include "Threshold.h"
#include <map>

namespace BlasBooster {

template <class Derived>
class OccupationPolicy
{
public:

    OccupationPolicy() = default;

    /// Return number of values which fulfill the valueChecker
    template <class ValueChecker>
    size_t getNbOfSignificantElements(ValueChecker const& valueChecker) const
    {
        auto key = std::shared_ptr<ValueCheckerBase>(new ValueChecker(valueChecker));
        if (nbDesiredElementsMap_.count(key)) {
            return nbDesiredElementsMap_[key];
        } else {
            size_t nbDesiredElements = countDesiredElements(*(static_cast<const Derived*>(this)),valueChecker);
            nbDesiredElementsMap_[key] = nbDesiredElements;
            return nbDesiredElements;
        }
    }

    /// Return occupation of values which fulfill the valueChecker
    template <class ValueChecker>
    double getOccupation(ValueChecker const& valueChecker) const
    {
        return static_cast<double>(getNbOfSignificantElements(valueChecker))
            / static_cast<const Derived*>(this)->getSize();
    }

    template <class ValueChecker>
    bool isOccupationLargerThan(double value, ValueChecker const& valueChecker) const
    {
        return getOccupation(valueChecker) > value;
    }

    template <class ValueChecker>
    bool isOccupationSmallerThan(double value, ValueChecker const& valueChecker) const
    {
        return getOccupation(valueChecker) < value;
    }

    void reset()
    {
        nbDesiredElementsMap_.clear();
    }

private:

    mutable std::map<std::shared_ptr<ValueCheckerBase>,size_t,ValueCheckerLess> nbDesiredElementsMap_;

};

} // namespace BlasBooster
