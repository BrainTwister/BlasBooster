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
struct TypeList{};

using List = TypeList<Derived1, Derived2>;

using DynType = std::shared_ptr<Base>;

template <class T>
struct MyFunctor
{
    std::string operator() (T const& t) {
        return T::name();
    }
    std::string operator() (DynType const& dynType) {
        return this->operator()(*std::static_pointer_cast<T>(dynType));
    }
};

template <>
struct MyFunctor<DynType>
{
	MyFunctor() {
        dynFunc.push_back(MyFunctor<Derived1>());
        dynFunc.push_back(MyFunctor<Derived2>());
    }

    std::string operator() (DynType const& dynType) {
        return dynFunc[dynType->getIdx()](dynType);
    }

    std::vector<std::function<std::string(DynType const&)>> dynFunc;
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
