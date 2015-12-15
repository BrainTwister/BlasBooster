#ifndef BLASBOOSTER_UTILITIES_SERIALIZE_H_
#define BLASBOOSTER_UTILITIES_SERIALIZE_H_

#include "BlasBooster/Utilities/Filesystem.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>
#include <type_traits>

inline boost::property_tree::ptree read_xml_tree(filesystem::path const& path)
{
    std::ifstream ifs(path.string());
    if (!ifs) throw std::runtime_error("Error opening file " + path.string());
    boost::property_tree::ptree tree;
    boost::property_tree::read_xml(ifs, tree);
    return tree;
}

template <class T, class Enable = void>
struct GenericLoader
{
    T operator () (boost::property_tree::ptree const& tree, std::string const& name, T def) const
	{
    	return tree.get<T>(name, def);
	}
};

template <class T>
struct GenericLoader<T, typename std::enable_if<T::IsSetting>::type>
{
    T operator () (boost::property_tree::ptree const& tree, std::string const& name, T def) const
	{
        return T(tree.get_child(name));
	}
};

#endif // BLASBOOSTER_UTILITIES_SERIALIZE_H_
