#include "BlasBooster/Utilities/Serialize.h"
#include "BlasBooster/Utilities/Settings.h"
#include <boost/property_tree/json_parser.hpp>
#include "gtest/gtest.h"
#include <string>

// Test polymorphism

struct Base
{
    virtual ~Base() {};
    virtual std::string get() const;
};

struct Derived1 : public Base
{
    BLASBOOSTER_SERIALIZE(Derived1, \
        ((int, i, 2.3)) \
        ((std::string, s, "bar")) \
    )

    virtual std::string get() const { return s; }

    int i;
    std::string s;
};

struct Derived2 : public Base
{
    BLASBOOSTER_SERIALIZE(Derived2, \
        ((double, d, 2.3)) \
        ((std::string, s, "bar")) \
    )

    virtual std::string get() const { return s; }

    double d;
    std::string s;
};

BLASBOOSTER_SETTINGS_REGISTER(Base, \
    (Derived1) \
    (Derived2) \
)

BLASBOOSTER_SETTINGS(Settings, \
    ((std::shared_ptr<Base>, p1, std::shared_ptr<Base>())) \
    ((std::shared_ptr<Base>, p2, std::shared_ptr<Derived1>())) \
)

TEST(SerializeTest, default)
{
    Settings settings;

    EXPECT_EQ(std::shared_ptr<Base>(), settings.p1);
    EXPECT_EQ(std::shared_ptr<Derived1>(), settings.p2);
}

TEST(SerializeTest, parameter_constructor)
{
    std::shared_ptr<Base> p1 = std::make_shared<Derived1>();
    Settings settings(p1);

    EXPECT_EQ(4, std::dynamic_pointer_cast<Derived1>(settings.p1)->i);
}

TEST(SerializeTest, construct_by_json)
{
    std::stringstream ss("{\"p1\": {\"Derived1\": {\"i\": 42}}}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings settings(pt);

    EXPECT_EQ(42, std::dynamic_pointer_cast<Derived1>(settings.p1)->i);
}

TEST(SerializeTest, construct_by_json_2)
{
    std::stringstream ss("{\"p1\": {\"Derived1\": {\"i\": 42}}, \"p2\": {\"Derived2\": {\"d\": 3.9}}}");
    boost::property_tree::ptree pt;
    read_json(ss, pt);
    Settings settings(pt);

    EXPECT_EQ(42, std::dynamic_pointer_cast<Derived1>(settings.p1)->i);
    EXPECT_EQ(3.9, std::dynamic_pointer_cast<Derived2>(settings.p2)->d);
}
