#pragma once

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
