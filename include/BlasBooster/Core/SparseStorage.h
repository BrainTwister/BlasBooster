#ifndef SPARSESTORAGE_H_
#define SPARSESTORAGE_H_

#include "Storage.h"
#include <boost/serialization/access.hpp>

namespace BlasBooster {

/**
 * /brief Fixed size storage class for sparse arrays.
 */
template <class ValueType, class IndexType, bool FixedSize, size_t Size>
class SparseStorage
{
public:

    typedef SparseStorage<ValueType,IndexType,FixedSize,Size> self;
    typedef ValueType* pointer;
    typedef const ValueType* const_pointer;
    typedef __gnu_cxx::__normal_iterator<pointer,self> iterator;
    typedef __gnu_cxx::__normal_iterator<const_pointer,self> const_iterator;

    SparseStorage()
     : data_()
    {}

    /// Copy constructor
    SparseStorage( const self& other )
     : data_()
    {
        // TODO: check for efficiency (memcopy?)
        std::copy_n(other.begin(),other.size(),begin());
    }

    ~SparseStorage() {}

    /// Copy assignment operator
    SparseStorage& operator = ( const self& rhs ) {

         if ( &rhs == this ) {
             std::copy_n(rhs.begin(),rhs.size(),this->begin());
         }

         return *this;
    }

    bool operator == ( const SparseStorage& rhs ) const {
        return data_ == rhs.data_
        and    size_ == rhs.size_;
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

private:

    template < class T2, class I2, bool F2, size_t S2 >
    friend class SparseStorage;

    ValueType data_[Size];

    static const size_t size_ = Size;

};

/**
 * /brief Flexible size storage class for sparse arrays.
 */
template <class ValueType, class IndexType>
class SparseStorage<ValueType,IndexType,false,0>
{
public:

    typedef SparseStorage<ValueType,IndexType,false,0> self;
    typedef ValueType* pointer;
    typedef const ValueType* const_pointer;
    typedef IndexType* index_pointer;
    typedef const IndexType* const_index_pointer;
    typedef typename Storage<ValueType,false,false,0>::iterator iterator;
    typedef typename Storage<ValueType,false,false,0>::const_iterator const_iterator;
    typedef typename Storage<IndexType,false,false,0>::iterator index_iterator;
    typedef typename Storage<IndexType,false,false,0>::const_iterator const_index_iterator;

    /// Default constructor
    SparseStorage(IndexType nbOfValues = 0, IndexType nbOfOffsets = 0)
     : value_(nbOfValues),
       key_(nbOfValues),
       offset_(nbOfOffsets)
    {}

    /// Conversion constructor
    template <class T2, class I2, bool F2, size_t S2>
    SparseStorage(SparseStorage<T2,I2,F2,S2> const& rhs)
     : value_(rhs.value_),
       key_(rhs.key_),
       offset_(rhs.offset_)
    {}

    void resize(IndexType nbOfValues, IndexType nbOfOffsets) {
        value_.resize(nbOfValues);
        key_.resize(nbOfValues);
        offset_.resize(nbOfOffsets);
    }

    bool operator == ( const SparseStorage& rhs ) const {
        return offset_ == rhs.offset_ and key_ == rhs.key_ and value_ == rhs.value_;
    }

    template < class T2, class I2, bool F2, size_t S2 >
    bool equal( const SparseStorage<T2,I2,F2,S2>& rhs ) const {
        return offset_.equal(rhs.offset_) and key_.equal(rhs.key_) and value_.equal(rhs.value_);
    }

    template < class T2, class I2, bool F2, size_t S2 >
    bool notEqual( const SparseStorage<T2,I2,F2,S2>& rhs ) const {
        return !equal(rhs);
    }

    iterator begin() { return value_.begin(); }
    const_iterator begin() const { return value_.begin(); }
    iterator end() { return value_.end(); }
    const_iterator end() const { return value_.end(); }

    index_iterator beginKey() { return key_.begin(); }
    const_index_iterator beginKey() const { return key_.begin(); }
    index_iterator endKey() { return key_.end(); }
    const_index_iterator endKey() const { return key_.end(); }

    index_iterator beginOffset() { return offset_.begin(); }
    const_index_iterator beginOffset() const { return offset_.begin(); }
    index_iterator endOffset() { return offset_.end(); }
    const_index_iterator endOffset() const { return offset_.end(); }

    IndexType size() { return value_.size(); }
    IndexType sizeOffset() { return offset_.size(); }

protected:

    template < class T2, class I2, bool F2, size_t S2 >
    friend class SparseStorage;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & value_;
        ar & key_;
        ar & offset_;
    }

    Storage<ValueType,false,false,0> value_;
    Storage<IndexType,false,false,0> key_;
    Storage<IndexType,false,false,0> offset_;

};

} // namespace BlasBooster

#endif /* SPARSESTORAGE_H_ */
