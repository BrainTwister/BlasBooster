#ifndef STRIDEDCURSORBASE_H_
#define STRIDEDCURSORBASE_H_

#include <boost/operators.hpp>

namespace BlasBooster {

/**
 * StridedCursorBase
 */
template < class Key >
struct StridedCursorBase
 : CursorBase<Key>,
   boost::equality_comparable< StridedCursorBase<Key> >
{
    typedef StridedCursorBase self;
    typedef CursorBase<Key> base;

    StridedCursorBase() : base(), stride_(0) {}

    StridedCursorBase( Key key, size_t stride ) : base(key), stride_(stride) {}

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

#endif // STRIDEDCURSORBASE_H_
