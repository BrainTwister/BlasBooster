#include "BlasBooster/Core/BlockedMatrix.h"
#include "BlasBooster/Core/DenseMatrix.h"
#include "BlasBooster/Core/BlockSizeGenerator.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace BlasBooster;

TEST(BlockSizeGenerator, get_block_size)
{
    auto block_size = BlockSizeGenerator(0, 2).get_block_size(std::vector<size_t>{0,1,0});
    EXPECT_EQ((std::vector<size_t>{2,2}), block_size);
}

TEST(BlockSizeGenerator, get_block_size_2)
{
    auto block_size = BlockSizeGenerator(2, 5).get_block_size(std::vector<float>{0,0,0,0,15,0,0,0,0,15,0,0,0,0,0,0,0,0,0});
    EXPECT_EQ((std::vector<size_t>{5,5,5,5}), block_size);
}

TEST(BlockSizeGenerator, functor)
{
    // TODO: Provide matrices over a factory with unique identifier
    DynamicMatrix F5(new Matrix<Dense,double>(5, 5, AllFiller<double>(0.1)));
    DynamicMatrix Z5(new Matrix<Dense,double>(5, 5, AllFiller<double>(0.0)));

    auto&& A = Matrix<Dense, double>{BlockedDenseMatrix{
        {Z5,Z5,Z5,Z5},
        {Z5,F5,Z5,Z5},
        {Z5,Z5,Z5,Z5},
        {Z5,Z5,Z5,Z5}
    }};

    auto&& [bs_detect_row, bs_detect_col] = BlockSizeGenerator(2, 5).get_detection_arrays(A);

    EXPECT_EQ(0.0, bs_detect_row[0]);
    EXPECT_EQ(15.0, bs_detect_row[4]);

    auto&& [bs_row, bs_col] = BlockSizeGenerator(2, 5)(A);

    EXPECT_EQ((std::vector<size_t>{5,5,5,5}), bs_row);
}
