#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <sstream>
#include <set>
#include <string>

namespace pt = boost::property_tree;

struct Settings
{
    std::string str;
    int level;
    std::set<std::string> modules;
    Settings& load(std::istream& is);
    void save(std::ostream& os) const;
};

Settings& Settings::load(std::istream& is)
{
    pt::ptree tree;
    pt::read_xml(is, tree);
    str = tree.get<std::string>("str");
    level = tree.get("level", 0);
    //for (auto & elem : modules) modules.insert(elem.second.data());
    return *this;
}

void Settings::save(std::ostream& os) const
{
    pt::ptree tree;
    tree.put("str", str);
    tree.put("level", level);
    //for (auto const& elem : modules) tree.add("root.modules.module", elem);
    pt::write_xml(os, tree);
}

int main()
{
    Settings settings;
    std::istringstream iss("<level>42</level><str>Hello</str>");
    settings.load(iss).save(std::cout);
}
