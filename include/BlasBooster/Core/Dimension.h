// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef DIMENSION_H_
#define DIMENSION_H_

#include "BlasBooster/Utilities/Noexcept.h"
#include <boost/operators.hpp>
#include <boost/serialization/access.hpp>
#include <cstddef>

namespace BlasBooster {

class NoLeadingDimension {};
class NoUnblockedDimension {};

namespace fixed {

template < class IndexType, IndexType NbRows = 0, IndexType NbColumns = 0 >
struct Dimension
{
    static const bool fixed = true;
    static const IndexType nbRows = NbRows;
    static const IndexType nbColumns = NbColumns;
    static const IndexType size = NbRows * NbColumns;

    Dimension( IndexType = 0, IndexType = 0 ) {}

    IndexType getNbRows() const { return nbRows; }
    IndexType getNbColumns() const { return nbColumns; }
    IndexType getSize() const { return size; }
};

} // namespace fixed

namespace nonfixed {

template <class IndexType>
struct Dimension
 : boost::equality_comparable<Dimension<IndexType> >
{
	typedef Dimension self;
    static const bool fixed = false;
    static const IndexType size = 0;

    Dimension(IndexType nbRows = 0, IndexType nbColumns = 0)
     : nbRows_(nbRows), nbColumns_(nbColumns)
    {}

    /// Default copy constructor
    Dimension(Dimension const& other) = default;

    /// Default copy assignment operator
    Dimension& operator = (Dimension const& other) = default;

    /// Move constructor
    Dimension(Dimension&& other)
	 : nbRows_(other.nbRows_), nbColumns_(other.nbColumns_)
	{
		other.nbRows_ = 0;
		other.nbColumns_ = 0;
	}

    /// Move assignment
    Dimension& operator = (Dimension&& other) BLASBOOSTER_NOEXCEPT
    {
		nbRows_ = other.nbRows_;
		nbColumns_ = other.nbColumns_;
		other.nbRows_ = 0;
		other.nbColumns_ = 0;
	}

    friend void swap(self& a, self& b) BLASBOOSTER_NOEXCEPT
    {
    	using std::swap; // bring in swap for built-in types
    	swap(a.nbRows_,b.nbRows_);
    	swap(a.nbColumns_,b.nbColumns_);
    }

    bool operator == (self const& rhs) const
    {
        return this->nbRows_ == rhs.nbRows_ and this->nbColumns_ == rhs.nbColumns_;
    }

    IndexType getNbRows() const { return nbRows_; }
    IndexType getNbColumns() const { return nbColumns_; }
    IndexType getSize() const { return nbRows_ * nbColumns_; }

protected:

    IndexType nbRows_;
    IndexType nbColumns_;

private:

    friend class boost::serialization::access;

    template < class Archive >
    void serialize( Archive & ar, const unsigned int version )
    {
        ar & nbRows_;
        ar & nbColumns_;
    }

};

template < class IndexType >
struct LeadingDimension
{
    LeadingDimension( IndexType ldRows = 0, IndexType ldColumns = 0 )
     : ldRows_(ldRows), ldColumns_(ldColumns)
    {}

    IndexType getLdRows() const { return ldRows_; }
    IndexType getLdColumns() const { return ldColumns_; }

protected:

    IndexType ldRows_;
    IndexType ldColumns_;

};

template < class IndexType >
struct UnblockedDimension
{
    UnblockedDimension( IndexType ubRows = 0, IndexType ubColumns = 0 )
     : ubRows_(ubRows), ubColumns_(ubColumns)
    {}

    IndexType getUnblockedRows() const { return ubRows_; }
    IndexType getUnblockedColumns() const { return ubColumns_; }

protected:

    IndexType ubRows_;
    IndexType ubColumns_;

};

} // namespace nonfixed
} // namespace BlasBooster

#endif /* DIMENSION_H_ */
