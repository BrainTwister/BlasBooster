#ifndef BLASBOOSTER_UTILITIES_SETTINGS_H_
#define BLASBOOSTER_UTILITIES_SETTINGS_H_

#include "BlasBooster/Utilities/Filesystem.h"
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
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

#define MACRO_SINGLE_INITIALIZE_DEFAULT(r,size,i,elem)\
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,2,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_DEFAULT(SEQ)\
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_DEFAULT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_INITIALIZE_ARGUMENTS(r,size,i,elem)\
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_ARGUMENTS(SEQ)\
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_ARGUMENTS,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_CONSTRUCTOR_ARGUMENT(r,size,i,elem)\
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CONSTRUCTOR_ARGUMENTS(SEQ)\
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_CONSTRUCTOR_ARGUMENT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_MEMBER(r,data,elem)\
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem);

#define PRINT_CLASS_MEMBERS(SEQ)\
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER,,SEQ)

#define MACRO_SINGLE_MEMBER_LOAD(r,data,elem)\
    BOOST_PP_TUPLE_ELEM(3,1,elem) = GenericLoader<BOOST_PP_TUPLE_ELEM(3,0,elem)>()(tree,\
    	BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)), BOOST_PP_TUPLE_ELEM(3,2,elem));

#define PRINT_CLASS_MEMBERS_LOAD(SEQ)\
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER_LOAD,,SEQ)

#define BLASBOOSTER_SETTINGS(Name,Members)\
    class Name\
    {\
    public:\
\
        Name()\
         : PRINT_INITIALIZE_DEFAULT(Members)\
        {}\
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members))\
         : PRINT_INITIALIZE_ARGUMENTS(Members)\
        {}\
\
        Name(boost::property_tree::ptree const& tree)\
        {\
            PRINT_CLASS_MEMBERS_LOAD(Members)\
        }\
\
        Name(filesystem::path const& path)\
		 : Name(read_xml_tree(path))\
        {}\
\
        PRINT_CLASS_MEMBERS(Members)\
\
	    static const bool IsSetting = true;\
    };
// end macro BLASBOOSTER_SETTINGS

#endif // BLASBOOSTER_UTILITIES_SETTINGS_H_
