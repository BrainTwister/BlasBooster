#pragma once

#include "BlasBooster/Utilities/Noexcept.h"
#include <boost/serialization/access.hpp>
#include <cstddef>
#include <utility>

namespace BlasBooster {

/// Matrix is stored row-wise (C-style).
struct RowMajor{};

/// Matrix is stored column-wise (Fortran-style).
struct ColumnMajor{};

/// Dimension is determined during compile-time.
template <size_t NbRows = 0, size_t NbColumns = 0>
struct FixedSize
{
    static const size_t nbRows = NbRows;
    static const size_t nbColumns = NbColumns;
};

/// Dimension is determined during run-time.
struct VariableSize {};

template <class SizeArg, class OrientationArg>
struct Dimension
{
    static const bool fixed = true;
    static const size_t nbRows = SizeArg::NbRows;
    static const size_t nbColumns = SizeArg::NbColumns;
    static const size_t size = nbRows * nbColumns;

    Dimension(size_t = 0, size_t = 0) {}

    size_t getNbRows() const { return nbRows; }
    size_t getNbColumns() const { return nbColumns; }
    size_t getSize() const { return size; }
};

template <class OrientationArg>
struct Dimension<VariableSize, OrientationArg>
{
    static const bool fixed = false;
    static const size_t size = 0;

    Dimension(size_t nbRows = 0, size_t nbColumns = 0)
     : nbRows_(nbRows), nbColumns_(nbColumns), full_size_(nbRows * nbColumns)
    {}

    /// Default copy constructor
    Dimension(Dimension const& other) = default;

    /// Default copy assignment operator
    Dimension& operator = (Dimension const& other) = default;

    /// Default move constructor
    Dimension(Dimension&& other) = default;

    /// Default move assignment
    Dimension& operator = (Dimension&& other) = default;

    friend void swap(Dimension& a, Dimension& b) BLASBOOSTER_NOEXCEPT
    {
        std::swap(a.nbRows_, b.nbRows_);
        std::swap(a.nbColumns_, b.nbColumns_);
        std::swap(a.full_size_, b.full_size_);
    }

    bool operator == (Dimension const& rhs) const
    {
        return this->nbRows_ == rhs.nbRows_ and this->nbColumns_ == rhs.nbColumns_;
    }

    bool operator != (Dimension const& rhs) const
    {
        return !operator==(rhs);
    }

    size_t getNbRows() const { return nbRows_; }
    size_t getNbColumns() const { return nbColumns_; }
    size_t getSize() const { return full_size_; }

    template <class U = OrientationArg>
    size_t getMajorDimension(typename std::enable_if<std::is_same<U, RowMajor>::value>::type* = 0) const {
        return nbColumns_;
    }

    template <class U = OrientationArg>
    size_t getMajorDimension(typename std::enable_if<std::is_same<U, ColumnMajor>::value>::type* = 0) const {
        return nbRows_;
    }

    template <class U = OrientationArg>
    size_t getMinorDimension(typename std::enable_if<std::is_same<U, RowMajor>::value>::type* = 0) const {
        return nbRows_;
    }

    template <class U = OrientationArg>
    size_t getMinorDimension(typename std::enable_if<std::is_same<U, ColumnMajor>::value>::type* = 0) const {
        return nbColumns_;
    }

protected:

    size_t nbRows_;
    size_t nbColumns_;
    size_t full_size_;

private:

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & nbRows_;
        ar & nbColumns_;
        ar & full_size_;
    }
};

struct NoLeadingDimension {};

struct LeadingDimension
{
    LeadingDimension(size_t ldRows = 0, size_t ldColumns = 0)
     : ldRows_(ldRows), ldColumns_(ldColumns)
    {}

    size_t getLdRows() const { return ldRows_; }
    size_t getLdColumns() const { return ldColumns_; }

protected:

    size_t ldRows_;
    size_t ldColumns_;

};

struct NoUnblockedDimension {};

struct UnblockedDimension
{
    UnblockedDimension(size_t ubRows = 0, size_t ubColumns = 0)
     : ubRows_(ubRows), ubColumns_(ubColumns)
    {}

    size_t getUnblockedRows() const { return ubRows_; }
    size_t getUnblockedColumns() const { return ubColumns_; }

protected:

    size_t ubRows_;
    size_t ubColumns_;

};

} // namespace BlasBooster
