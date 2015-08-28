// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_ABSOLUTEVALUERANGECHECKER_H_
#define BLASBOOSTER_CORE_ABSOLUTEVALUERANGECHECKER_H_

#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Core/CoreException.h"
#include <cmath>
#include <memory>

namespace BlasBooster {

struct NoBound {};
struct ExclusiveBound {};
struct InclusiveBound {};

struct ValueCheckerBase
{
    virtual bool operator < (ValueCheckerBase const& other) const = 0;
    virtual size_t getID() const = 0;
};

struct ValueCheckerLess
{
    bool operator () (std::shared_ptr<ValueCheckerBase> const& v1, std::shared_ptr<ValueCheckerBase> const& v2) const
    {
        assert(v1 and v2);
        return *v1 < *v2;
    }
};

/**
 * Functor returning true if the absolute value is within the range lowerThreshold < abs(value) <= upperThreshold
 * Throws if upperThreshold is not larger than lowerThreshold.
 */
template <class ThresholdType, class LowerBound = ExclusiveBound, class UpperBound = NoBound>
class AbsoluteValueRangeChecker;

using ValueCheckerTypeList = TypeList <
    AbsoluteValueRangeChecker<double, ExclusiveBound, NoBound>,
    AbsoluteValueRangeChecker<double, ExclusiveBound, InclusiveBound>,
    AbsoluteValueRangeChecker<double, InclusiveBound, InclusiveBound>,
    AbsoluteValueRangeChecker<double, ExclusiveBound, ExclusiveBound>
>;

template <class ThresholdType>
class AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,NoBound> : public ValueCheckerBase
{
public:

    typedef AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,NoBound> self;

    AbsoluteValueRangeChecker(ThresholdType threshold = 0.0)
     : threshold_(threshold)
    {
        if (threshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: threshold < 0.0");
    }

    template <class ValueType>
    bool operator () (ValueType value) const
    {
        return std::abs(value) > threshold_;
    }

    bool operator < (ValueCheckerBase const& other) const
    {
        size_t otherID = other.getID();
        return std::tie(id_,threshold_)
            < std::tie(otherID,
            static_cast<AbsoluteValueRangeChecker const&>(other).threshold_);
    }

    size_t getID() const { return id_; }

    static const size_t id_;

private:

    ThresholdType threshold_;

};

template <class ThresholdType>
const size_t AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,NoBound>::id_
    = GetIndex<AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,NoBound>, ValueCheckerTypeList>::value;

template <class ThresholdType>
class AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,InclusiveBound> : public ValueCheckerBase
{
public:

    typedef AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,InclusiveBound> self;

    AbsoluteValueRangeChecker(ThresholdType lowerThreshold, ThresholdType upperThreshold)
     : lowerThreshold_(lowerThreshold), upperThreshold_(upperThreshold)
    {
        if (lowerThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold < 0.0");
        if (upperThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: upperThreshold < 0.0");
        if (lowerThreshold >= upperThreshold) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold >= upperThreshold");
    }

    template <class ValueType>
    bool operator () (ValueType value) const
    {
        double absValue = std::abs(value);
        return absValue > lowerThreshold_ and absValue <= upperThreshold_;
    }

    bool operator < (ValueCheckerBase const& other) const
    {
        size_t otherID = other.getID();
        return std::tie(id_,lowerThreshold_,upperThreshold_)
            < std::tie(otherID,
            static_cast<AbsoluteValueRangeChecker const&>(other).lowerThreshold_,
            static_cast<AbsoluteValueRangeChecker const&>(other).upperThreshold_);
    }

    size_t getID() const { return id_; }

    static const size_t id_;

private:

    ThresholdType lowerThreshold_;
    ThresholdType upperThreshold_;

};

template <class ThresholdType>
const size_t AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,InclusiveBound>::id_
    = GetIndex<AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,InclusiveBound>, ValueCheckerTypeList>::value;

template <class ThresholdType>
class AbsoluteValueRangeChecker<ThresholdType,InclusiveBound,InclusiveBound> : public ValueCheckerBase
{
public:

    typedef AbsoluteValueRangeChecker<ThresholdType,InclusiveBound,InclusiveBound> self;

    AbsoluteValueRangeChecker(ThresholdType lowerThreshold, ThresholdType upperThreshold)
     : lowerThreshold_(lowerThreshold), upperThreshold_(upperThreshold)
    {
        if (lowerThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold < 0.0");
        if (upperThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: upperThreshold < 0.0");
        if (lowerThreshold > upperThreshold) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold > upperThreshold");
    }

    template <class ValueType>
    bool operator () (ValueType value) const
    {
        double absValue = std::abs(value);
        return absValue >= lowerThreshold_ and absValue <= upperThreshold_;
    }

    bool operator < (ValueCheckerBase const& other) const
    {
        size_t otherID = other.getID();
        return std::tie(id_,lowerThreshold_,upperThreshold_)
            < std::tie(otherID,
            static_cast<AbsoluteValueRangeChecker const&>(other).lowerThreshold_,
            static_cast<AbsoluteValueRangeChecker const&>(other).upperThreshold_);
    }

    size_t getID() const { return id_; }

    static const size_t id_;

private:

    ThresholdType lowerThreshold_;
    ThresholdType upperThreshold_;

};

template <class ThresholdType>
const size_t AbsoluteValueRangeChecker<ThresholdType,InclusiveBound,InclusiveBound>::id_
    = GetIndex<AbsoluteValueRangeChecker<ThresholdType,InclusiveBound,InclusiveBound>, ValueCheckerTypeList>::value;

template <class ThresholdType>
class AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,ExclusiveBound> : public ValueCheckerBase
{
public:

    typedef AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,ExclusiveBound> self;

    AbsoluteValueRangeChecker(ThresholdType lowerThreshold, ThresholdType upperThreshold)
     : lowerThreshold_(lowerThreshold), upperThreshold_(upperThreshold)
    {
        if (lowerThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold < 0.0");
        if (upperThreshold < 0.0) throw CoreException("AbsoluteValueRangeChecker: upperThreshold < 0.0");
        if (lowerThreshold >= upperThreshold) throw CoreException("AbsoluteValueRangeChecker: lowerThreshold >= upperThreshold");
    }

    template <class ValueType>
    bool operator () (ValueType value) const
    {
        double absValue = std::abs(value);
        return absValue > lowerThreshold_ and absValue < upperThreshold_;
    }

    bool operator < (ValueCheckerBase const& other) const
    {
        size_t otherID = other.getID();
        return std::tie(id_,lowerThreshold_,upperThreshold_)
            < std::tie(otherID,
            static_cast<AbsoluteValueRangeChecker const&>(other).lowerThreshold_,
            static_cast<AbsoluteValueRangeChecker const&>(other).upperThreshold_);
    }

    size_t getID() const { return id_; }

    static const size_t id_;

private:

    ThresholdType lowerThreshold_;
    ThresholdType upperThreshold_;

};

template <class ThresholdType>
const size_t AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,ExclusiveBound>::id_
    = GetIndex<AbsoluteValueRangeChecker<ThresholdType,ExclusiveBound,ExclusiveBound>, ValueCheckerTypeList>::value;

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_ABSOLUTEVALUERANGECHECKER_H_
