// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef THRESHOLD_H_
#define THRESHOLD_H_

#include "BlasBooster/Core/TypeList.h"
#include "BlasBooster/Utilities/wrong_t.h"
#include "BlasBooster/Preprocessor/CreateSettingsClass.h"
#include <boost/mpl/long.hpp>
#include <boost/mpl/vector.hpp>

namespace BlasBooster {

/// Global type for all thresholds
typedef double ThresholdType;

BLASBOOSTER_CREATE_SETTINGS_CLASS( ThresholdSettings,\
    (( ThresholdType, significanceThresholdSinglePrecision, std::numeric_limits<float>::epsilon() ))\
    (( ThresholdType, significanceThresholdDoublePrecision, std::numeric_limits<double>::epsilon() ))\
    (( ThresholdType, occupationThresholdMatrixSparseFloatSinglePrecision, 0.0 ))\
    (( ThresholdType, occupationThresholdMatrixSparseFloatDoublePrecision, 0.2 ))\
    (( ThresholdType, occupationThresholdMatrixDenseFloatSinglePrecision, 0.0 ))\
    (( ThresholdType, occupationThresholdMatrixDenseFloatDoublePrecision, 1.0 ))\
    (( ThresholdType, occupationThresholdMatrixSparseDoubleSinglePrecision, 0.2 ))\
    (( ThresholdType, occupationThresholdMatrixSparseDoubleDoublePrecision, 0.2 ))\
    (( ThresholdType, occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision, 0.2 ))\
    (( ThresholdType, occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision, 0.4 ))\
    (( ThresholdType, occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision, 0.2 ))\
    (( ThresholdType, occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision, 1.0 ))\
    (( ThresholdType, occupationThresholdMatrixDenseDoubleSinglePrecision, 1.0 ))\
    (( ThresholdType, occupationThresholdMatrixDenseDoubleDoublePrecision, 1.0 ))\
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
	 : settings_(settings)
	{}

	Threshold& operator = (Threshold const& other)
	{
		if (&other != this) {
	        settings_ = other.settings_;
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

	ThresholdSettings settings_;

};

template <>
struct SignificanceThresholdDistributor<float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.significanceThresholdSinglePrecision_; }
};

template <>
struct SignificanceThresholdDistributor<double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.significanceThresholdDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,float>,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixSparseFloatSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,float>,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixSparseFloatDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> >,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMultipleMatrixSparseDoubleSparseFloatSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>,Matrix<Sparse,float> >,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMultipleMatrixSparseDoubleSparseFloatDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>, Matrix<Dense,float> >,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMultipleMatrixDenseFloatSparseDoubleSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<MultipleMatrix< Matrix<Sparse,double>, Matrix<Dense,float> >,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMultipleMatrixDenseFloatSparseDoubleDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,double>,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixSparseDoubleSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Sparse,double>,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixSparseDoubleDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,float>,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixDenseFloatSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,float>,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixDenseFloatDoublePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,double>,float>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixDenseDoubleSinglePrecision_; }
};

template <>
struct OccupationThresholdDistributor<Matrix<Dense,double>,double>
{
	ThresholdType operator () (Threshold const& threshold) const { return threshold.settings_.occupationThresholdMatrixDenseDoubleDoublePrecision_; }
};

} // namespace BlasBooster

#endif /* THRESHOLD_H_ */
