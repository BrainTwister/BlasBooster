#pragma once

#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/MatrixConverter.h"
#include "BlasBooster/Core/SparseMatrix.h"
#include "BlasBooster/Utilities/BlasBoosterException.h"
#include "BlasBooster/Utilities/STLHelpers.h"
#include <numeric>
#include <set>
#include <tuple>

namespace BlasBooster {

template <class T>
auto sort_indices(std::vector<T> const& v)
{
    // initialize original index locations
    std::vector<size_t> idx(v.size());
    iota(idx.begin(), idx.end(), 0);

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(), [&v](size_t i1, size_t i2) {
        return v[i1] > v[i2];
    });

    return idx;
}

struct BlockSizeGenerator
{
    BlockSizeGenerator(size_t min_block_size, size_t max_block_size)
     : min_block_size(min_block_size), max_block_size(max_block_size)
    {
        if (2*min_block_size > max_block_size) throw BlasBoosterException("BlockSizeGenerator: max_block_size must be at least twice as large as min_block_size.");
    }

    template <class T, class P>
    std::tuple<std::vector<size_t>, std::vector<size_t>> operator () (Matrix<Dense,T,P> const& matrix) const;

    template <class T, class P>
    std::tuple<std::vector<size_t>, std::vector<size_t>, std::vector<size_t>> matrix_matrix_mult(Matrix<Dense,T,P> const& A, Matrix<Dense,T,P> const& B) const;

    template <class T, class P>
    std::tuple<std::vector<T>, std::vector<T>> get_detection_arrays(Matrix<Dense,T,P> const& matrix) const;

private:

    template <class T>
    std::vector<size_t> get_block_size(std::vector<T> const& detect) const;

    size_t min_block_size;
    size_t max_block_size;

};

template <class T, class P>
std::tuple<std::vector<size_t>, std::vector<size_t>> BlockSizeGenerator::operator () (Matrix<Dense,T,P> const& matrix) const
{
    // TODO: if only one is larger then max_block_size, only this detection matrix must be build
    if (matrix.getNbRows() <= max_block_size and matrix.getNbColumns() <= max_block_size)
        return std::make_tuple(std::vector<size_t>(1, matrix.getNbRows()), std::vector<size_t>(1, matrix.getNbColumns()));

    auto&& [row_detect, col_detect] = get_detection_arrays(matrix);
    return std::make_tuple(get_block_size(row_detect), get_block_size(col_detect));
}

template <class T, class P>
std::tuple<std::vector<size_t>, std::vector<size_t>, std::vector<size_t>> BlockSizeGenerator::matrix_matrix_mult(Matrix<Dense,T,P> const& A, Matrix<Dense,T,P> const& B) const
{
    auto&& [row_detect_A, col_detect_A] = get_detection_arrays(A);
    auto&& [row_detect_B, col_detect_B] = get_detection_arrays(B);

    std::transform(col_detect_A.begin(), col_detect_A.end(),
        row_detect_B.begin(), col_detect_A.begin(), std::plus<size_t>());

    return std::make_tuple(get_block_size(row_detect_A), get_block_size(col_detect_A), get_block_size(col_detect_B));
}

template <class T, class P>
std::tuple<std::vector<T>, std::vector<T>> BlockSizeGenerator::get_detection_arrays(Matrix<Dense,T,P> const& matrix) const
{
    Matrix<Dense,T,P> matrix_log(matrix);
    for (auto&& value : matrix_log) {
        if (value != 0.0) value = std::log10(value);
    }

    std::vector<T> row_detect(matrix.getNbRows() - 1, 0.0);
    std::vector<T> col_detect(matrix.getNbColumns() - 1, 0.0);

    typename Matrix<Dense,T,P>::const_iterator iter1(matrix_log.begin()),
        iter2(matrix_log.begin() + 1), iter3(matrix_log.begin() + matrix.getNbColumns());

    for (size_t i = 0; i != matrix.getNbRows() - 1; ++i)
    {
        for (size_t j = 0; j != matrix.getNbColumns() - 1; ++j, ++iter1, ++iter2, ++iter3)
        {
            row_detect[i] += std::abs(*iter1 - *iter3);
            col_detect[j] += std::abs(*iter1 - *iter2);
        }
        row_detect[i] += std::abs(*iter1 - *iter3);
        ++iter1, ++iter2, ++iter3;
    }

    for (size_t j = 0; j != matrix.getNbColumns() - 1; ++j, ++iter1, ++iter2)
    {
        col_detect[j] += std::abs(*iter1 - *iter2);
    }

    return std::make_tuple(row_detect, col_detect);
}

template <class T>
std::vector<size_t> BlockSizeGenerator::get_block_size(std::vector<T> const& detect) const
{
    auto&& sorted_indices = sort_indices(detect);
    std::set<size_t> borders{0, detect.size() + 1};
    std::set<size_t> large_blocks{0};

    for (size_t i = 0; i != detect.size();)
    {
        // Find last index which has the equal detect value
        std::set<size_t> equal_indices{i};
        for (size_t j = i+1; j != detect.size(); ++j) {
            if (detect[sorted_indices[i]] == detect[sorted_indices[j]]) equal_indices.insert(j);
            else break;
        }

        // Attention: early increase of index i
        i += equal_indices.size();

        // Find next index which divide his current block so that the smaller one is the largest
        while (!equal_indices.empty()) {
            size_t largest_min = 0;
            size_t idx, left_idx, left, right;
            size_t next_j, next_idx, next_left_idx, next_left, next_right;
            for (auto&& j : equal_indices) {
                idx = sorted_indices[j] + 1;
                left_idx = *(std::prev(borders.lower_bound(idx)));
                left = idx - left_idx;
                right = *borders.upper_bound(idx) - idx;
                if (left < min_block_size or right < min_block_size) continue;
                if (std::min(left, right) > largest_min) {
                    largest_min = std::min(left, right);
                    next_j = j;
                    next_idx = idx;
                    next_left_idx = left_idx;
                    next_left = left;
                    next_right = right;
                }
            }
            equal_indices.erase(next_j);
            borders.insert(next_idx);
            if (large_blocks.find(next_left_idx) != large_blocks.end())
            {
                if (next_left <= max_block_size) large_blocks.erase(next_left_idx);
                if (next_right > max_block_size) large_blocks.insert(next_idx);
            }
            if (large_blocks.empty()) break;
        }
        if (large_blocks.empty()) break;
    }

    // Generate border_size from borders
    std::vector<size_t> block_size(borders.size() - 1);
    auto&& iter1(borders.begin()), iter2(++borders.begin()), iterEnd(borders.end());
    auto&& iter3(block_size.begin());

    for (; iter2 != iterEnd; ++iter1, ++iter2, ++iter3) {
        *iter3 = *iter2 - *iter1;
    }

    return block_size;
}

} // namespace BlasBooster
