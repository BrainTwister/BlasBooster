#pragma once

#include "BlasBooster/Core/Matrix.h"
#include "BlasBooster/Core/MultipleMatrix.h"
#include "BlasBooster/Utilities/TypeList.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include "BrainTwister/Record.h"
#include <limits>

namespace BlasBooster {

/// Global type for all thresholds
typedef double ThresholdType;

BRAINTWISTER_RECORD( ThresholdSettings, \
    ((ThresholdType, significanceThresholdSinglePrecision, std::numeric_limits<float>::epsilon())) \
    ((ThresholdType, significanceThresholdDoublePrecision, std::numeric_limits<double>::epsilon())) \
    ((ThresholdType, occupationThresholdMatrixSparseFloatSinglePrecision, 0.0)) \
    ((ThresholdType, occupationThresholdMatrixSparseFloatDoublePrecision, 0.2)) \
    ((ThresholdType, occupationThresholdMatrixDenseFloatSinglePrecision, 0.0)) \
    ((ThresholdType, occupationThresholdMatrixDenseFloatDoublePrecision, 1.0)) \
    ((ThresholdType, occupationThresholdMatrixSparseDoubleSinglePrecision, 0.2)) \
    ((ThresholdType, occupationThresholdMatrixSparseDoubleDoublePrecision, 0.2)) \
    ((ThresholdType, occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision, 0.2)) \
    ((ThresholdType, occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision, 0.4)) \
    ((ThresholdType, occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision, 0.2)) \
    ((ThresholdType, occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision, 1.0)) \
    ((ThresholdType, occupationThresholdMatrixDenseDoubleSinglePrecision, 1.0)) \
    ((ThresholdType, occupationThresholdMatrixDenseDoubleDoublePrecision, 1.0)) \
)

template <class T>
class SignificanceThresholdDistributor
{
    static_assert(wrong_t<T>::value, "SignificanceThresholdDistributor: Primary template must not be instantiated.");
};

template <class M, class T>
class OccupationThresholdDistributor
{
    static_assert(wrong_t<T>::value, "OccupationThresholdDistributor: Primary template must not be instantiated.");
};

class Threshold
{
public:

    Threshold(ThresholdSettings const& settings = ThresholdSettings())
     : settings(settings)
    {}

    Threshold& operator = (Threshold const& other)
    {
        if (&other != this) {
            settings = other.settings;
        }
        return *this;
    }

    template <class T>
    ThresholdType getSignificanceThreshold() const { return SignificanceThresholdDistributor<T>()(*this); }

    template <class M, class T>
    ThresholdType getOccupationThreshold() const { return OccupationThresholdDistributor<M,T>()(*this); }

private:

    template <class T>
    friend class SignificanceThresholdDistributor;

    template <class M, class T>
    friend class OccupationThresholdDistributor;

    ThresholdSettings settings;

};

template <>
struct SignificanceThresholdDistributor<float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.significanceThresholdSinglePrecision; }
};

template <>
struct SignificanceThresholdDistributor<double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.significanceThresholdDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,float>,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixSparseFloatSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,float>,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixSparseFloatDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> >,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> >,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>, Matrix<Dense,float> >,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>, Matrix<Dense,float> >,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,double>,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixSparseDoubleSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,double>,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixSparseDoubleDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,float>,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixDenseFloatSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,float>,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixDenseFloatDoublePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,double>,float>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixDenseDoubleSinglePrecision; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,double>,double>
{
    ThresholdType operator () (Threshold const& threshold) const { return threshold.settings.occupationThresholdMatrixDenseDoubleDoublePrecision; }
};

} // namespace BlasBooster
