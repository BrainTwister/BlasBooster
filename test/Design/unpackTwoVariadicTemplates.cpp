#include "gtest/gtest.h"

template <typename ... Args> struct Tuple {};
template <typename T1, typename T2> struct Pair {};

template <class ... Args1> struct zip {
    template <class ... Args2> struct with {
        typedef Tuple<Pair<Args1, Args2> ... > type;
    };
};

typedef zip<short, int>::with<unsigned short, unsigned>::type T1;

template <typename ...> struct inner_unpack {};

template <class T, class ... Args>
struct inner_unpack<T, Tuple<Args...>>
{
    typedef Tuple<Pair<T, Args> ... > type;
};

template <typename ...> struct unpack {};

template <typename List, typename ... Args2>
struct unpack<List, Tuple<Args2...>>
{
    typedef Tuple<typename inner_unpack<Args2, List>::type ... > type;
};

typedef Tuple<int, short, double> L;

typedef unpack<L, L>::type T2;

TEST(Design, unpackTwoVariadicTemplates)
{
    EXPECT_TRUE((std::is_same<T1,
        Tuple<Pair<short, unsigned short>, Pair<int, unsigned int>>>::value));
    EXPECT_TRUE((std::is_same<T2,
        Tuple<Tuple<Pair<int, int>, Pair<int, short>, Pair<int, double> >,
        Tuple<Pair<short, int>, Pair<short, short>, Pair<short, double> >,
        Tuple<Pair<double, int>, Pair<double, short>, Pair<double, double>>>>::value));
}
