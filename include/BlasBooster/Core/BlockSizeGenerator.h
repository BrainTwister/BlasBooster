#pragma once

#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixConverter.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/STLHelpers.h"
#include <set>

namespace BlasBooster {

template <class T>
std::vector<size_t> getSortedIndex(std::vector<T> const& v)
{
  // initialize original index locations
  std::vector<size_t> idx(v.size());
  for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] > v[i2];});

  return idx;
}

/**
 *  Using a single block size to decompose a matrix generally a block with less elements remain.\n
 *  Therefore there are two possibilities:\n
 *  -# SymmetricDistribution: Distribute the remaining elements to the other blocks\n
 *  -# ExtraBlockAtTheEnd: Add an additional block with the remaining elements at the end.
 */
enum BehaviorOfRemainingElements { SymmetricDistribution, ExtraBlockAtTheEnd };

std::vector<size_t> generateBlockSizeList(size_t nbElements, size_t blockSize, BehaviorOfRemainingElements behaviorOfRemainingElements);

struct BlockSizeGenerator
{
    BlockSizeGenerator(size_t minBlockSize, size_t maxBlockSize)
     : minBlockSize_(minBlockSize), maxBlockSize_(maxBlockSize)
    {
        if (2*minBlockSize > maxBlockSize) throw BlasBoosterException("BlockSizeGenerator: maxBlockSize must be at least twice as large as minBlockSize.");
    }

    template <class T, class P>
    std::pair<std::vector<size_t>, std::vector<size_t> > operator () (Matrix<Dense,T,P> const& matrix) const;

private:

    template <class T>
    int getExponent(T value) const;

    template <class T>
    std::vector<size_t> getBlockSizeList(std::vector<T> const& detectionArray, size_t size) const;

    size_t minBlockSize_;
    size_t maxBlockSize_;

};

template <class T, class P>
std::pair<std::vector<size_t>, std::vector<size_t>> BlockSizeGenerator::operator () (Matrix<Dense,T,P> const& matrix) const
{
    size_t i, j;
    size_t nbRows = matrix.getNbRows();
    size_t nbColumns = matrix.getNbColumns();
    size_t nbRowsMinus1 = matrix.getNbRows() - 1;
    size_t nbColumnsMinus1 = matrix.getNbColumns() - 1;

    // TODO: if only one is larger then maxBlockSize, only this detection matrix must be build
    if (nbRows <= maxBlockSize_ and nbColumns <= maxBlockSize_) return std::make_pair(std::vector<size_t>(1, nbRows), std::vector<size_t>(1, nbColumns));

    typename Matrix<Dense,T,P>::const_iterator iter1(matrix.begin()), iter2(matrix.begin() + 1), iter3(matrix.begin() + nbColumns);
    int exp1, exp2, exp3;

    std::vector<T> rowDetection(nbRowsMinus1, 0.0);
    std::vector<T> columnDetection(nbColumnsMinus1, 0.0);

    for (i = 0; i != nbRowsMinus1; ++i)
    {
        for (j = 0; j != nbColumnsMinus1; ++j, ++iter1, ++iter2, ++iter3)
        {
            exp1 = getExponent(*iter1);
            exp2 = getExponent(*iter2);
            exp3 = getExponent(*iter3);
            rowDetection[i] += std::abs(exp1 - exp3);
            columnDetection[j] += std::abs(exp1 - exp2);
        }
        exp1 = getExponent(*iter1);
        exp3 = getExponent(*iter3);
        rowDetection[i] += std::abs(exp1 - exp3);
        ++iter1, ++iter2, ++iter3;
    }

    for (j = 0; j != nbColumnsMinus1; ++j, ++iter1, ++iter2)
    {
        exp1 = getExponent(*iter1);
        exp2 = getExponent(*iter2);
        columnDetection[j] += std::abs(exp1 - exp2);
    }

    return std::make_pair(getBlockSizeList(rowDetection, nbRows),
    		              getBlockSizeList(columnDetection, nbColumns));
}

template <class T>
int BlockSizeGenerator::getExponent(T value) const
{
    int exponent;
    if (value != 0.0) frexp(value,&exponent);
    else exponent = std::numeric_limits<T>::min_exponent;
    return exponent;
}

template <class T>
std::vector<size_t> BlockSizeGenerator::getBlockSizeList(std::vector<T> const& detectionArray, size_t size) const
{
    auto sortedIndex = getSortedIndex(detectionArray);

    std::set<size_t> borders{0,size};
    std::set<size_t> largeBlocks{0};

    size_t curIndex, beforeIndex, afterIndex;
    for (size_t i(0); i != detectionArray.size(); ++i) {
        curIndex = sortedIndex[i] + 1;
        beforeIndex = *(std::prev(borders.lower_bound(curIndex)));
        afterIndex = *borders.upper_bound(curIndex);
        if (curIndex - beforeIndex >= minBlockSize_ and afterIndex - curIndex >= minBlockSize_)
        {
            borders.insert(curIndex);
            if (largeBlocks.find(beforeIndex) != largeBlocks.end())
            {
                if (curIndex - beforeIndex <= maxBlockSize_) largeBlocks.erase(beforeIndex);
                if (afterIndex - curIndex > maxBlockSize_) largeBlocks.insert(curIndex);
            }
        }
        if (largeBlocks.empty()) break;
    }

    std::vector<size_t> blockSizeList(borders.size()-1);

    std::set<size_t>::const_iterator iterBorder1(borders.begin()), iterBorder2(++borders.begin()), iterBorderEnd(borders.end());
    std::vector<size_t>::iterator iterCur(blockSizeList.begin());

    for ( ; iterBorder2 != iterBorderEnd; ++iterCur, ++iterBorder1, ++iterBorder2) {
        *iterCur = *iterBorder2 - *iterBorder1;
    }

    return blockSizeList;
}

} // namespace BlasBooster
