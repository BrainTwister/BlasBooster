#ifndef STRIPEDITERATOR_H_
#define STRIPEDITERATOR_H_

#include <boost/iterator/iterator_facade.hpp>
#include <iterator>

template <class T>
class StripedIterator
 : public boost::iterator_facade <
       StripedIterator<T>,
       T,
       boost::bidirectional_traversal_tag
   >
{

public:

    StripedIterator()
     : iter_(nullptr), position_(0), block_(0), continuousSizeMinus1_(0), separatorSizePlus1_(0), nbBlocks_(0)
    {}

    StripedIterator(T* iter, size_t position, size_t block, size_t continuousSize, size_t separatorSize, size_t nbBlocks)
     : iter_(iter), position_(position), block_(block),
       continuousSizeMinus1_(continuousSize-1), separatorSizePlus1_(separatorSize+1), nbBlocks_(nbBlocks)
    {}

    template <class T2>
    StripedIterator(StripedIterator<T2> const& other)
     : iter_(other.iter_), position_(other.position_), block_(other.block_),
       continuousSizeMinus1_(other.continuousSizeMinus1_), separatorSizePlus1_(other.separatorSizePlus1_), nbBlocks_(other.nbBlocks_)
    {}

private:

    template <class T2>
    friend class StripedIterator;

    friend class boost::iterator_core_access;

    T& dereference() const
    {
        return *iter_;
    }

    bool equal(StripedIterator const& other) const
    {
        return iter_ == other.iter_;
    }

    void increment()
    {
        if (position_ == continuousSizeMinus1_) {
            if (static_cast<size_t>(++block_) == nbBlocks_) ++iter_;
            else iter_ += separatorSizePlus1_;
            position_ = 0;
        } else {
            ++iter_;
            ++position_;
        }
    }

    void decrement()
    {
        if (position_ == 0) {
            if (--block_ == -1) --iter_;
            else iter_ -= separatorSizePlus1_;
            position_ = continuousSizeMinus1_;
        } else {
            --iter_;
            --position_;
        }
    }

    T* iter_;

    // Current position within the continuous memory space
    size_t position_;

    // Current continuous memory space block
    int block_;

    size_t continuousSizeMinus1_;

    size_t separatorSizePlus1_;

    size_t nbBlocks_;

};

#endif // STRIPEDITERATOR_H_
