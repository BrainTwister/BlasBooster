#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <range/v3/view/indices.hpp>
#include <range/v3/view/zip.hpp>

TEST(range_v3, zip)
{
    using namespace ranges;

    std::vector<int> a{9,8,7};
    std::vector<std::string> b{"a", "b", "c"};

    std::stringstream ss;
    for (auto&& [a,b,c] : view::zip(a, b, view::indices(a.size()))) {
        ss << a << b << c;
    }

    EXPECT_EQ("9a08b17c2", ss.str());
}
