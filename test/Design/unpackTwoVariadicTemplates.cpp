#include <iostream>
#include <typeinfo>

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

typedef unpack<L, L>::type T3;

int main()
{
    std::cout << typeid(T1).name() << std::endl;
    std::cout << typeid(T3).name() << std::endl;
}
