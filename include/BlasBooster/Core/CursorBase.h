// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef BLASBOOSTER_CORE_CURSORBASE_H_
#define BLASBOOSTER_CORE_CURSORBASE_H_

namespace BlasBooster {

template <class Key>
struct CursorBase
{
    typedef CursorBase self;

    CursorBase() : key_() {}

    CursorBase(Key key) : key_(key) {}

    virtual ~CursorBase() {}

    template <class OtherCursor>
    bool operator == (OtherCursor const& other) const
    {
        return key_ == other.key_;
    }

    template <class OtherCursor>
    bool operator != (OtherCursor const& other) const
    {
        return !operator==(other);
    }

    self& operator ++ ()
    {
        ++key_;
        return *this;
    }

    self& operator -- ()
    {
        --key_;
        return *this;
    }

    Key key_;

}; // class CursorBase

} // namespace BlasBooster

#endif // BLASBOOSTER_CORE_CURSORBASE_H_
