#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

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
    void operator() (T const& t) {
        std::cout << "MyFunctor was called for " << T::name() << std::endl;
    }
    void operator() (DynType const& dynType) {
        this->operator()(*std::static_pointer_cast<T>(dynType));
    }
};

template <class ListType>
struct DynamicFunctor
{
    DynamicFunctor() {
        dynFunc.push_back(MyFunctor<Derived1>());
        dynFunc.push_back(MyFunctor<Derived2>());
    }

    void operator() (DynType const& dynType) {
        dynFunc[dynType->getIdx()](dynType);
    }

    std::vector<std::function<void(DynType const&)>> dynFunc;
};

template <>
struct MyFunctor<DynType> : DynamicFunctor<List>
{};

int main()
{
    Derived1 d1;
    MyFunctor<Derived1>()(d1);

    Derived2 d2;
    MyFunctor<Derived2>()(d2);

    DynType dyn1(new Derived1);
    MyFunctor<DynType>()(dyn1);

    DynType dyn2(new Derived2);
    MyFunctor<DynType>()(dyn2);
}

