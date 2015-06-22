// Copyright (C) 2012-2015, Bernd Doser (service@braintwister.eu)
// All rights reserved.
//
// This file is part of BlasBooster
//
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE
// TERMS OF THE COPYRIGHT NOTICE

#ifndef STORAGE_H_
#define STORAGE_H_

#include "BlasBooster/Core/CoreException.h"
#include "BlasBooster/Core/StripedIterator.h"
#include "BlasBooster/Utilities/DebugPrint.h"
#include "BlasBooster/Utilities/EqualWithinNumericalAccuracy.h"
#include "BlasBooster/Utilities/Noexcept.h"
#include <boost/serialization/split_member.hpp>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>

namespace BlasBooster {

/// Fixed size storage class for dense arrays on stack.
template <class ElementType, bool OnStack, bool isFixed, size_t Size, bool Strided = false>
class Storage
{
public:

    typedef Storage<ElementType,OnStack,isFixed,Size,Strided> self;
    typedef ElementType* pointer;
    typedef ElementType const* const_pointer;
    typedef __gnu_cxx::__normal_iterator<pointer,self> iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer,self> const_iterator;

    Storage(size_t = 0)
     : data_()
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onStack): Default constructor is called.");
    }

    /// Copy constructor
    Storage(self const& other)
     : data_()
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onStack): Copy constructor is called.");
        std::copy(other.begin(),other.end(),begin());
    }

    /// Copy assignment operator
    Storage& operator = (self const& rhs)
    {
         if ( this != &rhs ) {
             std::copy_n(rhs.begin(),rhs.size(),this->begin());
         }
         return *this;
    }

#ifndef NO_INITIALIZER_LIST_SUPPORTED
    /// Initializer list constructor
    Storage(std::initializer_list<ElementType> values)
     : data_()
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onStack): Initializer list constructor is called.");
        size_t i(0);
        for (auto val : values) data_[i++] = val;
    }
#endif

    bool operator == ( const self& rhs ) const {
        return data_ == rhs.data_ and size_ == rhs.size_;
    }

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    bool equal(Storage<T2,onStack2,isFixed2,Size2,Strided2> const& rhs) const
    {
        if ( size_ != rhs.size_ ) return false;
        for ( size_t i(0); i != size_; ++i ) {
            if ( !equalWithinNumericalAccuracy(data_[i],rhs.data_[i]) ) return false;
        }
        return true;
    }

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    bool notEqual(Storage<T2,onStack2,isFixed2,Size2,Strided2> const& rhs) const
    {
        return !equal(rhs);
    }

    iterator begin() {
        return iterator(data_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    size_t size() const {
        return size_;
    }

    pointer getDataPointer() {
        return data_;
    }

    const_pointer getDataPointer() const {
        return data_;
    }

private:

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    friend class Storage;

    ElementType data_[Size];

    static const size_t size_ = Size;

};

/**
 * /brief Fixed size storage class for dense arrays on heap.
 */
template <class ElementType, size_t Size>
class Storage<ElementType,false,true,Size,false>
{
public:

    typedef Storage<ElementType,false,true,Size,false> self;
    typedef ElementType* pointer;
    typedef ElementType const* const_pointer;
    typedef __gnu_cxx::__normal_iterator<pointer,self> iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer,self> const_iterator;

    /// Default constructor
    Storage( size_t = 0 )
     : data_(new ElementType[size_]), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Default constructor is called.");
    }

#ifndef NO_INITIALIZER_LIST_SUPPORTED
    /// Initializer list constructor
    Storage( std::initializer_list<ElementType> values )
     : data_(new ElementType[size_]), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Initializer list constructor is called.");
        if ( values.size() != size_ ) throw std::runtime_error("Storage (fixed,onHeap): values.size() != size_");
        size_t i(0);
        for ( auto val : values ) data_[i++] = val;
    }
#endif

    /// Copy constructor
    Storage( const Storage& rhs )
     : data_(new ElementType[size_]), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Copy constructor is called.");
        std::copy(rhs.begin(),rhs.end(),begin());
    }

    /// Move constructor
    Storage( Storage&& rhs )
     : data_(rhs.data_), ownMemory_(rhs.ownMemory_)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Move constructor is called.");
        rhs.ownMemory_ = false;
    }

    /// Conversion constructor
    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    Storage( const Storage<T2,onStack2,isFixed2,Size2,Strided2>& rhs )
     : data_(new ElementType[size_]), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Conversion constructor is called.");
        if ( rhs.size_ != size_ ) throw std::runtime_error("Storage (fixed,onHeap): rhs.size_ != size_");
        std::copy(rhs.begin(),rhs.end(),begin());
    }

    /// Proxy constructor using external memory
    Storage( ElementType* ptrExternalData, size_t size )
     : data_(ptrExternalData), ownMemory_(false)
    {}

    ~Storage() {
        if (ownMemory_) delete [] data_;
    }

    /// Copy assignment
    Storage& operator = ( const self& rhs ) {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Copy assignment is called.");
        if ( this != &rhs ) {
            if ( rhs.size_ != size_ ) throw std::runtime_error("Storage (fixed,onHeap): rhs.size_ != size_");
            std::copy_n(rhs.begin(),rhs.size_,begin());
            ownMemory_ = true;
        }
        return *this;
    }

    /// Move assignment
    Storage& operator = ( self&& rhs ) BLASBOOSTER_NOEXCEPT {
        BLASBOOSTER_DEBUG_PRINT("Storage (fixed,onHeap): Move assignment is called.");
        swap(*this,rhs);
        return *this;
    }

    friend void swap( self& a, self& b ) BLASBOOSTER_NOEXCEPT {
        using std::swap; // bring in swap for built-in types
        swap(a.data_,b.data_);
        swap(a.ownMemory_,b.ownMemory_);
    }

    bool operator == ( const Storage& rhs ) const {
        return data_ == rhs.data_ and ownMemory_ == rhs.ownMemory_;
    }

    template < class T2, bool onStack2, bool isFixed2, size_t Size2 >
    bool equal( const Storage<T2,onStack2,isFixed2,Size2>& rhs ) const {
        if ( size_ != rhs.size_ ) return false;
        typename Storage<T2,onStack2,isFixed2,Size2>::const_iterator iter2(rhs.begin());
        for ( size_t i(0); i != size_; ++i ) {
            if ( !equalWithinNumericalAccuracy(data_[i],rhs.data_[i]) ) return false;
        }
        return true;
    }

    template < class T2, bool onStack2, bool isFixed2, size_t Size2 >
    bool notEqual( const Storage<T2,onStack2,isFixed2,Size2>& rhs ) const {
        return !equal(rhs);
    }

    iterator begin() {
        return iterator(data_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    size_t size() const {
        return size_;
    }

    pointer getDataPointer() {
        return data_;
    }

    const_pointer getDataPointer() const {
        return data_;
    }

protected:

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    friend class Storage;

    friend class boost::serialization::access;

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template < class Archive >
    void save(Archive & ar, const unsigned int version) const
    {
        for ( size_t i(0); i != size_; ++i ) ar << data_[i];
    }

    template < class Archive >
    void load(Archive & ar, const unsigned int version)
    {
        for ( size_t i(0); i != size_; ++i ) ar >> data_[i];
        ownMemory_ = true;
    }

    ElementType* data_;

    static const size_t size_ = Size;

    /// If true memory is administrated by own class. Otherwise external memory is used.
    bool ownMemory_;

};

/**
 * /brief Flexible size class for dense arrays on heap.
 */
template <class ElementType>
class Storage<ElementType,false,false,0,false>
{
public:

    typedef Storage<ElementType,false,false,0,false> self;
    typedef ElementType* pointer;
    typedef ElementType const* const_pointer;
    typedef __gnu_cxx::__normal_iterator<pointer,self> iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer,self> const_iterator;

    /// Default constructor
    Storage()
     : data_(nullptr), size_(0), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Default constructor is called.");
    }

    /// Parameter constructor
    Storage( size_t size )
     : data_(new ElementType[size]), size_(size), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Parameter constructor is called.");
    }

#ifndef NO_INITIALIZER_LIST_SUPPORTED
    /// Initializer list constructor
    Storage( std::initializer_list<ElementType> values )
     : data_(new ElementType[values.size()]), size_(values.size()), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Initializer list constructor is called.");
        size_t i(0);
        for ( auto val : values ) data_[i++] = val;
    }
#endif

    /// Copy constructor
    Storage(Storage const& rhs)
     : data_(new ElementType[rhs.size_]), size_(rhs.size_), ownMemory_(rhs.ownMemory_)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Copy constructor is called.");
        std::copy(rhs.begin(),rhs.end(),begin());
    }

    /// Move constructor
    Storage(Storage&& rhs)
     : data_(rhs.data_), size_(rhs.size_), ownMemory_(rhs.ownMemory_)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Move constructor is called.");
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.ownMemory_ = false;
    }

    /// Conversion constructor
    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    Storage( const Storage<T2,onStack2,isFixed2,Size2,Strided2>& rhs )
     : data_(new ElementType[rhs.size_]), size_(rhs.size_), ownMemory_(true)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Conversion constructor is called.");
        std::copy(rhs.begin(),rhs.end(),begin());
    }

    /// Proxy constructor using external memory
    Storage( ElementType* ptrExternalData, size_t size )
     : data_(ptrExternalData), size_(size), ownMemory_(false)
    {}

    ~Storage() {
        if (ownMemory_ and data_) delete [] data_;
    }

    void resize(size_t size) {
        if (size_ == size) return;
        if (!ownMemory_) throw std::runtime_error("resize storage with not own memory.");
        if (data_) delete [] data_;
        data_ = new ElementType[size];
        size_ = size;
    }

    /// Copy assignment
    Storage& operator = ( const self& rhs ) {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Copy assignment is called.");
        if ( this != &rhs ) {
            if (ownMemory_) delete [] data_;
            if (rhs.ownMemory_) {
                data_ = new ElementType[rhs.size_];
                std::copy(rhs.begin(),rhs.end(),begin());
            } else {
                data_ = rhs.data_;
            }
            size_ = rhs.size_;
            ownMemory_ = rhs.ownMemory_;
        }
        return *this;
    }

    /// Move assignment
    Storage& operator = ( self&& rhs ) BLASBOOSTER_NOEXCEPT {
        BLASBOOSTER_DEBUG_PRINT("Storage (onHeap): Move assignment is called.");
        // clear own resources
        if (ownMemory_) delete [] data_;
        // steal other resources
        data_ = rhs.data_;
        size_ = rhs.size_;
        ownMemory_ = rhs.ownMemory_;
        // clean other resources
        rhs.data_ = nullptr;
        rhs.size_ = 0;
        rhs.ownMemory_ = false;
        return *this;
    }

    friend void swap( self& a, self& b ) BLASBOOSTER_NOEXCEPT
    {
        using std::swap; // bring in swap for built-in types
        swap(a.data_,b.data_);
        swap(a.size_,b.size_);
        swap(a.ownMemory_,b.ownMemory_);
    }

    bool operator == (Storage const& rhs) const
    {
        return data_ == rhs.data_
            and size_ == rhs.size_
            and ownMemory_ == rhs.ownMemory_;
    }

    template <class T2, bool onStack2, bool isFixed2, size_t Size2>
    bool equal(Storage<T2,onStack2,isFixed2,Size2> const& rhs) const
    {
        if (size_ != rhs.size_) return false;
        for (size_t i(0); i != size_; ++i) {
            if (!equalWithinNumericalAccuracy(data_[i],rhs.data_[i])) return false;
        }
        return true;
    }

    template <class T2, bool onStack2, bool isFixed2, size_t Size2>
    bool notEqual(Storage<T2,onStack2,isFixed2,Size2> const& rhs) const
    {
        return !equal(rhs);
    }

    iterator begin() {
        return iterator(data_);
    }

    const_iterator begin() const {
        return const_iterator(data_);
    }

    iterator end() {
        return iterator(data_ + size_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_);
    }

    size_t size() const {
        return size_;
    }

    pointer getDataPointer() {
        return data_;
    }

    const_pointer getDataPointer() const {
        return data_;
    }

protected:

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    friend class Storage;

    friend class boost::serialization::access;

    BOOST_SERIALIZATION_SPLIT_MEMBER()

    template <class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << size_;
        for ( size_t i(0); i != size_; ++i ) ar << data_[i];
    }

    template <class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> size_;
        data_ = new ElementType[size_];
        for ( size_t i(0); i != size_; ++i ) ar >> data_[i];
        ownMemory_ = true;
    }

    ElementType* data_;

    size_t size_;

    /// If true memory is administrated by own class. Otherwise external memory is used.
    bool ownMemory_;

};

/// Flexible size class for striped arrays on heap
/// Only available as proxy storage using external memory.
template <class ElementType>
class Storage<ElementType,false,false,0,true>
{
public:

    typedef Storage<ElementType,false,false,0,true> self;
    typedef ElementType* pointer;
    typedef ElementType const* const_pointer;
    typedef StripedIterator<ElementType> iterator;
    typedef StripedIterator<const ElementType> const_iterator;

    /// Default constructor
    Storage()
     : data_(nullptr), size_(0),
       continuousSize_(0), nbBlocks_(0), separatorSize_(0)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage<ElementType,false,false,0,true>: Default constructor is called.");
    }

    /// Parameter constructor
    Storage(ElementType* ptrExternalData, size_t continuousSize, size_t nbBlocks, size_t separatorSize)
     : data_(ptrExternalData), size_(continuousSize*nbBlocks),
       continuousSize_(continuousSize), nbBlocks_(nbBlocks), separatorSize_(separatorSize)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage<ElementType,false,false,0,true>: Parameter constructor is called.");
    }

    /// Copy constructor
    Storage(Storage const& rhs)
     : data_(rhs.data_), size_(rhs.size_),
       continuousSize_(rhs.continuousSize_), nbBlocks_(rhs.nbBlocks_), separatorSize_(rhs.separatorSize_)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage<ElementType,false,false,0,true>: Copy constructor is called.");
    }

    ~Storage() {}

    /// Copy assignment
    Storage& operator = (Storage const& rhs)
    {
        BLASBOOSTER_DEBUG_PRINT("Storage<ElementType,false,false,0,true>: Copy assignment is called.");
        if ( this != &rhs ) {
            data_ = rhs.data_;
            size_ = rhs.size_;
            continuousSize_ = rhs.continuousSize_;
            nbBlocks_ = rhs.nbBlocks_;
            separatorSize_ = rhs.separatorSize_;
        }
        return *this;
    }

    friend void swap(self& a, self& b) BLASBOOSTER_NOEXCEPT {
        using std::swap; // bring in swap for built-in types
        swap(a.data_,b.data_);
        swap(a.size_,b.size_);
        swap(a.continuousSize_,b.continuousSize_);
        swap(a.nbBlocks_,b.nbBlocks_);
        swap(a.separatorSize_,b.separatorSize_);
    }

    bool operator == (Storage const& rhs) const
    {
        return data_ == rhs.data_
            and size_ == rhs.size_
            and continuousSize_ == rhs.continuousSize_
            and nbBlocks_ == rhs.nbBlocks_
            and separatorSize_ == rhs.separatorSize_;
    }

//    template <class T2, bool onStack2, bool isFixed2, size_t Size2>
//    bool equal(Storage<T2,onStack2,isFixed2,Size2> const& rhs) const {
//        if ( size_ != rhs.size_ ) return false;
//        typename Storage<T2,onStack2,isFixed2,Size2>::const_iterator iter2(rhs.begin());
//        for ( size_t i(0); i != size_; ++i ) {
//            if ( !equalWithinNumericalAccuracy(data_[i],rhs.data_[i]) ) return false;
//        }
//        return true;
//    }
//
//    template <class T2, bool onStack2, bool isFixed2, size_t Size2>
//    bool notEqual(Storage<T2,onStack2,isFixed2,Size2> const& rhs) const {
//        return !equal(rhs);
//    }

    iterator begin() {
        return iterator(data_, 0, 0, continuousSize_, separatorSize_, nbBlocks_);
    }

    const_iterator begin() const {
        return const_iterator(data_, 0, 0, continuousSize_, separatorSize_, nbBlocks_);
    }

    iterator rbegin() {
        return iterator(data_ + size_ + (nbBlocks_-1) * separatorSize_ - 1, continuousSize_-1, nbBlocks_-1, continuousSize_, separatorSize_, nbBlocks_);
    }

    const_iterator rbegin() const {
        return iterator(data_ + size_ + (nbBlocks_-1) * separatorSize_ - 1, continuousSize_-1, nbBlocks_-1, continuousSize_, separatorSize_, nbBlocks_);
    }

    iterator end() {
        return iterator(data_ + size_ + (nbBlocks_-1) * separatorSize_, continuousSize_, nbBlocks_, continuousSize_, separatorSize_, nbBlocks_);
    }

    const_iterator end() const {
        return const_iterator(data_ + size_ + (nbBlocks_-1) * separatorSize_, continuousSize_, nbBlocks_, continuousSize_, separatorSize_, nbBlocks_);
    }

    iterator rend() {
        return iterator(data_ - 1, continuousSize_, -1, continuousSize_, separatorSize_, nbBlocks_);
    }

    const_iterator rend() const {
        return iterator(data_ - 1, continuousSize_, -1, continuousSize_, separatorSize_, nbBlocks_);
    }

    size_t size() const {
        return size_;
    }

    pointer getDataPointer() {
        return data_;
    }

    const_pointer getDataPointer() const {
        return data_;
    }

protected:

    template <class T2, bool onStack2, bool isFixed2, size_t Size2, bool Strided2>
    friend class Storage;

    template <class T2>
    friend class StripedIterator;

    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/) const
    {
        ar & data_;
        ar & size_;
        ar & continuousSize_;
        ar & nbBlocks_;
        ar & separatorSize_;
    }

    ElementType* data_;

    size_t size_;

    size_t continuousSize_;

    size_t nbBlocks_;

    size_t separatorSize_;

};

} // namespace BlasBooster

#endif /* STORAGE_H_ */
