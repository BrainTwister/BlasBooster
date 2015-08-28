// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_STRIDEDCURSORBASE_H_
#define BLASBOOSTER_CORE_STRIDEDCURSORBASE_H_

namespace BlasBooster {

/**
 * StridedCursorBase
 */
template <class Key>
struct StridedCursorBase
 : CursorBase<Key>
{
    typedef StridedCursorBase self;
    typedef CursorBase<Key> base;

    StridedCursorBase() : base(), stride_(0) {}

    StridedCursorBase(Key key, size_t stride) : base(key), stride_(stride) {}

    virtual ~StridedCursorBase() {}

    self& operator ++ ()
    {
        this->key_ += stride_;
        return *this;
    }

    self& operator -- ()
    {
        this->key_ -= stride_;
        return *this;
    }

    size_t stride_;

}; // class StridedCursorBase

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_STRIDEDCURSORBASE_H_
