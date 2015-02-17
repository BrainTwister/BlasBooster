// Copyright (C) 2012-2014, Bernd Doser (bernd.doser@gmx.de)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef CURSOR_H_
#define CURSOR_H_

#include "CursorBase.h"
#include "Direction.h"
#include "Parameter.h"
#include "StridedCursorBase.h"
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits.hpp>

using namespace BlasBooster::Direction;

namespace BlasBooster {

/// Primary template for all cursors.
//template < class Collection, class DirectionType >
//class Cursor;

/**
 * P: matrix parameter
 * O: wanted orientation
 * D: DirectionType
 * D1: wanted direction (row,column)
 * D2: wanted direction (major,minor)
 */
template < class P, class O, class D, class D1, class D2 >
struct DirectionMatchOrientation
{
    typedef typename boost::mpl::and_<
		boost::is_same< typename P::orientation, O >,
		boost::mpl::or_< boost::is_same< D, D1 >, boost::is_same< D, D2 > >
    >::type type;
};

template < class Collection, class DirectionType >
struct Cursor
 : public CursorBase< typename Collection::IndexType >
{
	typedef Collection collection;
	typedef typename Collection::IndexType IndexType;
	typedef typename Collection::pointer pointer;
	typedef typename Collection::const_pointer const_pointer;
	typedef Cursor< Collection, DirectionType > self;
	typedef DirectionType direction;
	typedef CursorBase<IndexType> base;

	typedef typename boost::mpl::if_<
	    boost::is_const<Collection>,
	    const_pointer,
	    pointer
	>::type pointer_type;

	Cursor( Collection& c, IndexType index ) : base(index), ref(c) {}

	virtual ~Cursor() {}

	IndexType operator * () const {
        return this->key_;
    }

	template < class U = typename Collection::parameter >
	pointer_type begin( typename boost::enable_if<
		typename DirectionMatchOrientation<U,RowMajor,DirectionType,Row,Minor>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_ * ref.getLdColumns();
	}

	template < class U = typename Collection::parameter >
	pointer_type begin( typename boost::enable_if<
	    typename DirectionMatchOrientation<U,ColumnMajor,DirectionType,Row,Major>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_;
	}

	template < class U = typename Collection::parameter >
	pointer_type begin( typename boost::enable_if<
		typename DirectionMatchOrientation<U,RowMajor,DirectionType,Column,Major>::type >::type* = 0 ) const
	{
	    return ref.getDataPointer() + this->key_;
    }

	template < class U = typename Collection::parameter >
	pointer_type begin( typename boost::enable_if<
	    typename DirectionMatchOrientation<U,ColumnMajor,DirectionType,Column,Minor>::type >::type* = 0 ) const
	{
	    return ref.getDataPointer() + this->key_ * ref.getLdRows();
	}

	template < class U = typename Collection::parameter >
	pointer_type end( typename boost::enable_if<
		typename DirectionMatchOrientation<U,RowMajor,DirectionType,Row,Minor>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_ * ref.getLdColumns() + ref.getNbColumns();
	}

	template < class U = typename Collection::parameter >
	pointer_type end( typename boost::enable_if<
		typename DirectionMatchOrientation<U,ColumnMajor,DirectionType,Row,Major>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_ + ref.getLdRows() * ref.getNbColumns();
	}

	template < class U = typename Collection::parameter >
	pointer_type end( typename boost::enable_if<
	    typename DirectionMatchOrientation<U,RowMajor,DirectionType,Column,Major>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_ + ref.getNbRows() * ref.getLdColumns();
	}

	template < class U = typename Collection::parameter >
	pointer_type end( typename boost::enable_if<
		typename DirectionMatchOrientation<U,ColumnMajor,DirectionType,Column,Minor>::type >::type* = 0 ) const
	{
		return ref.getDataPointer() + this->key_ * ref.getLdRows() + ref.getNbRows();
	}

	Collection& ref;
};

template < class T, class Orientation, class OuterDirection >
struct GetCursorBaseType {
	typedef typename boost::mpl::if_<
		boost::mpl::or_<
		   boost::mpl::and_<
			   boost::is_same< Orientation, ColumnMajor >,
			   boost::mpl::or_<
			       boost::is_same< OuterDirection, Column >,
                   boost::is_same< OuterDirection, Minor >
	           >
		   >,
		   boost::mpl::and_<
			   boost::is_same< Orientation, RowMajor >,
			   boost::mpl::or_<
			       boost::is_same< OuterDirection, Row >,
                   boost::is_same< OuterDirection, Minor >
	           >
		   >
	   >,
	   StridedCursorBase<T>,
	   CursorBase<T>
	>::type type;
};

template < class Collection, class InnerDirection, class OuterDirection >
struct Cursor< Cursor< Collection, InnerDirection >, OuterDirection >
 : public GetCursorBaseType<
	   typename boost::mpl::if_<
		   boost::is_const<Collection>,
		   typename Collection::const_pointer,
		   typename Collection::pointer
		>::type,
       typename Collection::orientation, OuterDirection
   >::type
{
	typedef Collection collection;
	typedef typename Collection::IndexType IndexType;
	typedef typename Collection::pointer pointer;
	typedef typename Collection::const_pointer const_pointer;
	typedef Cursor< Cursor< Collection, InnerDirection >, OuterDirection > self;
	typedef OuterDirection direction;

	typedef typename boost::mpl::if_<
	    boost::is_const<Collection>,
	    const_pointer,
	    pointer
	>::type pointer_type;

	typedef typename boost::mpl::if_<
	    boost::is_const<Collection>,
	    typename Collection::const_value_type,
	    typename Collection::value_type
	>::type value_type;

	typedef typename GetCursorBaseType<pointer_type,typename Collection::orientation,OuterDirection>::type base;

	template < class U = typename Collection::parameter >
	Cursor( Collection& /*c*/, pointer_type ptrData, typename boost::enable_if<
	    typename DirectionMatchOrientation<U,RowMajor,OuterDirection,Column,Major>::type >::type* = 0 )
	 : base( ptrData )
	{}

	template < class U = typename Collection::parameter >
	Cursor( Collection& c, pointer_type ptrData, typename boost::enable_if<
		typename DirectionMatchOrientation<U,ColumnMajor,OuterDirection,Column,Minor>::type >::type* = 0 )
	 : base( ptrData, c.getLdRows() )
	{}

	template < class U = typename Collection::parameter >
	Cursor( Collection& c, pointer_type ptrData, typename boost::enable_if<
		typename DirectionMatchOrientation<U,RowMajor,OuterDirection,Row,Minor>::type >::type* = 0 )
	 : base( ptrData, c.getLdColumns() )
	{}

	template < class U = typename Collection::parameter >
	Cursor( Collection& /*c*/, pointer_type ptrData, typename boost::enable_if<
		typename DirectionMatchOrientation<U,ColumnMajor,OuterDirection,Row,Major>::type >::type* = 0 )
	 : base( ptrData )
	{}

	virtual ~Cursor() {}

	value_type& operator * () const { return *this->key_; }

	value_type& operator [] ( size_t nb ) const { return *(this->key_ + nb); }

};

} // namespace BlasBooster

#endif // CURSOR_H_
