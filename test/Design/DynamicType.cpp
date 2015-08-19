#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "gtest/gtest.h"

struct Base
{ 
    static const std::string name() { return "Base"; }
    virtual int getIdx() = 0;
};

struct Derived1 : public Base
{
    static const std::string name() { return "Derived1"; }
    virtual int getIdx() { return 0; }
};

struct Derived2 : public Base
{
    static const std::string name() { return "Derived2"; }
    virtual int getIdx() { return 1; }
};

template <class... T>
struct TypeList
{};

using List = TypeList<Derived1, Derived2>;

using DynType = std::shared_ptr<Base>;

template <class T>
struct MyFunctor
{
    using Result = std::string;

    Result operator() (T const& t) {
        return T::name();
    }
    Result operator() (DynType const& dynType) {
        return this->operator()(*std::static_pointer_cast<T>(dynType));
    }
};

template <>
struct MyFunctor<DynType>
{
    using Result = std::string;
    using Function = std::function< Result(DynType const&) >;

    Result operator() (DynType const& dynType) {
        return dynFunc[dynType->getIdx()](dynType);
    }

    static Function dynFunc[2];
};

MyFunctor<DynType>::Function MyFunctor<DynType>::dynFunc[] =
{
    MyFunctor<Derived1>(),
    MyFunctor<Derived2>()
};

TEST(Design, DynamicType)
{
    Derived1 d1;
    EXPECT_EQ("Derived1", MyFunctor<Derived1>()(d1));

    Derived2 d2;
    EXPECT_EQ("Derived2", MyFunctor<Derived2>()(d2));

    DynType dyn1(new Derived1);
    EXPECT_EQ("Derived1", MyFunctor<DynType>()(dyn1));

    DynType dyn2(new Derived2);
    EXPECT_EQ("Derived2", MyFunctor<DynType>()(dyn2));
}

