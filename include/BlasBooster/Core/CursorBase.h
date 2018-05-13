#pragma once

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
