#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <memory>
#include <sstream>
#include <set>
#include <string>
#include "gtest/gtest.h"

namespace pt = boost::property_tree;

struct SettingsBase
{
	virtual ~SettingsBase() {};
	virtual std::string name() const = 0;
};

struct Derived1 : public SettingsBase
{
	virtual std::string name() const { return "Derived1"; }
    std::string str;
    Derived1& load(pt::ptree const& tree);
};

struct Derived2 : public SettingsBase
{
	virtual std::string name() const { return "Derived2"; }
    double d;
    Derived1& load(pt::ptree const& tree);
};

struct Settings2
{
    std::string str;
    int level;
    Settings2& load(pt::ptree const& tree);
};

Settings2& Settings2::load(pt::ptree const& tree)
{
    str = tree.get<std::string>("str");
    level = tree.get("level", 0);
    return *this;
}

struct Settings
{
    std::string str;
    int level;
    std::set<std::string> modules;
    Settings2 settings2;
    std::shared_ptr<SettingsBase> polymorph;

    Settings& load(pt::ptree const& tree);
    void save(std::ostream& os) const;
};

Settings& Settings::load(pt::ptree const& tree)
{
    str = tree.get<std::string>("str");
    level = tree.get("level", 0);
    for (auto const& elem : tree.get_child("modules")) modules.insert(elem.second.data());
    settings2.load(tree.get_child("settings2"));
    pt::ptree sub = tree.get_child("polymorph");
    assert(sub.size() == 1);

    return *this;
}

void Settings::save(std::ostream& os) const
{
    pt::ptree tree;
    tree.put("str", str);
    tree.put("level", level);
    for (auto const& elem : modules) tree.add("modules.module", elem);
    pt::write_xml(os, tree);
}

TEST(Design, BoostPropertyTree)
{
    Settings settings;
    std::istringstream iss("<level>42</level><str>Hello</str>"
    		               "<modules><module>Foo</module><module>Bar</module></modules>"
                           "<settings2><level>7</level><str>World</str></settings2>"
    		               "<polymorph><derived1><str>Hey</str></derived1></polymorph>");
    pt::ptree tree;
    pt::read_xml(iss, tree);
    settings.load(tree);
    EXPECT_EQ(settings.str, "Hello");
    EXPECT_EQ(settings.level, 42);
    EXPECT_NE(settings.modules.find("Foo"), settings.modules.end());
    EXPECT_NE(settings.modules.find("Bar"), settings.modules.end());
    EXPECT_EQ(settings.settings2.str, "World");
    EXPECT_EQ(settings.settings2.level, 7);
    //EXPECT_EQ(settings.polymorph->name(), "Derived1");
    //EXPECT_EQ(iss.str(), oss.str());
}
