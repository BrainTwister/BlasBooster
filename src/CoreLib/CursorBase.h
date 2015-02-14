#ifndef CURSORBASE_H_
#define CURSORBASE_H_

#include <boost/operators.hpp>

namespace BlasBooster {

/**
 * CursorBase
 */
template < class Key >
struct CursorBase
 : boost::equality_comparable< CursorBase<Key> >
{
	typedef CursorBase self;

    CursorBase() : key_() {}

    CursorBase( Key key ) : key_(key) {}

    virtual ~CursorBase() {}

    template < class OtherCursor >
    bool operator == ( const OtherCursor& other ) const
    {
        return key_ == other.key_;
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

#endif // CURSORBASE_H_
