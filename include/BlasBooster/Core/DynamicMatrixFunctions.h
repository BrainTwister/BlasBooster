// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef DYNAMICMATRIXFUNCTIONS_H_
#define DYNAMICMATRIXFUNCTIONS_H_

#include "BlasBooster/Core/AllMatrixTypes.h"
#include "BlasBooster/Core/TypeList.h"
#include "BlasBooster/Utilities/exec_if.h"
#include "BlasBooster/Utilities/exec_if_2dim.h"
#include "BlasBooster/Utilities/TypeChecker.h"

namespace BlasBooster {

struct DynamicGetNbRows
{
    typedef size_t result_type;

    DynamicGetNbRows(DynamicMatrix const& dynMatrix) : dynMatrix_(dynMatrix) {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->getNbRows();
    }

    DynamicMatrix dynMatrix_;
};

inline size_t getNbRows(DynamicMatrix const& dynMatrix)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicGetNbRows(dynMatrix));
}

struct DynamicGetNbColumns
{
    typedef size_t result_type;

    DynamicGetNbColumns(DynamicMatrix const& dynMatrix) : dynMatrix_(dynMatrix) {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->getNbColumns();
    }

    DynamicMatrix dynMatrix_;
};

inline size_t getNbColumns(DynamicMatrix const& dynMatrix)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicGetNbColumns(dynMatrix));
}

struct DynamicGetSize
{
    typedef size_t result_type;

    DynamicGetSize(DynamicMatrix const& dynMatrix) : dynMatrix_(dynMatrix) {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->getSize();
    }

    DynamicMatrix dynMatrix_;
};

inline size_t getSize( const DynamicMatrix& dynMatrix )
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicGetSize(dynMatrix));
}

struct DynamicGetNorm
{
    typedef double result_type;

    DynamicGetNorm(DynamicMatrix const& dynMatrix) : dynMatrix_(dynMatrix) {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->getNorm();
    }

    DynamicMatrix dynMatrix_;
};

inline double getNorm(DynamicMatrix const& dynMatrix)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicGetNorm(dynMatrix));
}

struct DynamicIsNormLargerThan
{
    typedef double result_type;

    DynamicIsNormLargerThan(DynamicMatrix const& dynMatrix, double value)
     : dynMatrix_(dynMatrix), value_(value)
    {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->isNormLargerThan(value_);
    }

    DynamicMatrix dynMatrix_;
    double value_;
};

inline bool isNormLargerThan(DynamicMatrix const& dynMatrix, double value)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicIsNormLargerThan(dynMatrix,value));
}

template <class ValueChecker>
struct DynamicGetOccupation
{
    typedef double result_type;

    DynamicGetOccupation(DynamicMatrix const& dynMatrix, ValueChecker const& valueChecker)
     : dynMatrix_(dynMatrix), valueChecker_(valueChecker)
    {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->getOccupation(valueChecker_);
    }

    DynamicMatrix dynMatrix_;
    ValueChecker const& valueChecker_;
};

template <class ValueChecker>
inline double getOccupation(DynamicMatrix const& dynMatrix, ValueChecker const& valueChecker)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicGetOccupation<ValueChecker>(dynMatrix,valueChecker));
}

template <class ValueChecker>
struct DynamicIsOccupationLargerThan
{
    typedef bool result_type;

    DynamicIsOccupationLargerThan(DynamicMatrix const& dynMatrix, double value, ValueChecker const& valueChecker)
     : dynMatrix_(dynMatrix), value_(value), valueChecker_(valueChecker)
    {}

    template <class T>
    result_type operator () (T* = 0) const
    {
        return boost::static_pointer_cast<T>(dynMatrix_)->isOccupationLargerThan(valueChecker_);
    }

    DynamicMatrix dynMatrix_;
    double value_;
    ValueChecker const& valueChecker_;
};

template <class ValueChecker>
inline bool isOccupationLargerThan(DynamicMatrix const& dynMatrix, double value, ValueChecker const& valueChecker)
{
    return exec_if<TypeList>(TypeChecker(dynMatrix->getTypeIndex()),DynamicIsOccupationLargerThan<ValueChecker>(dynMatrix,value,valueChecker));
}

} // namespace BlasBooster

#endif /* DYNAMICMATRIXFUNCTIONS_H_ */
