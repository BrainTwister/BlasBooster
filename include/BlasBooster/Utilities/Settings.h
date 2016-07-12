#ifndef BLASBOOSTER_UTILITIES_SETTINGS_H_
#define BLASBOOSTER_UTILITIES_SETTINGS_H_

#include "BlasBooster/Utilities/Filesystem.h"
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>
#include <fstream>
#include <type_traits>

namespace BlasBooster {
namespace SettingsDetails {

template <class T>
struct is_setting
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template<typename U>
    static yes check(U*, typename U::is_setting* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

template <class T>
struct is_base_setting
{
  private:
    typedef char no;
    struct yes { no m[2]; };

    static T* make();
    template<typename U>
    static yes check(U*, typename U::is_base_setting* = 0);
    static no check(...);

  public:
    static bool const value = sizeof(check(make())) == sizeof(yes);
};

template <class Base>
struct PolymorphicLoader
{
    std::shared_ptr<Base> operator () (boost::property_tree::ptree const& pt) const;
};

/// Primary template for fundamental types
template <class T, class Enable = void>
struct GenericLoader
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& key, T def) const
	{
    	return pt.get<T>(key, def);
	}

    T operator () (boost::property_tree::ptree const& pt) const
	{
    	return pt.get_value<T>();
	}
};

/// Specialization for nested settings
template <class T>
struct GenericLoader<T, typename std::enable_if<is_setting<T>::value>::type>
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& key, T def) const
	{
		if (pt.count(key) == 0) return def;
        return T(pt.get_child(key));
	}

    T operator () (boost::property_tree::ptree const& pt) const
	{
        return T(pt);
	}
};

template <class T>
struct GenericLoader<std::vector<T>>
{
	std::vector<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::vector<T> def) const
	{
		if (pt.count(key) == 0) return def;
		std::vector<T> r;
		for (auto const& item : pt.get_child(key)) r.push_back(GenericLoader<T>()(item.second));
		return r;
	}
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<!is_base_setting<T>::value>::type>
{
	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
	{
		if (pt.count(key) == 0) return def;
		else if (pt.count(key) > 1) throw std::runtime_error("More than one key found for " + key + ".");

		return std::shared_ptr<T>(new T(pt.get<T>(key)));
	}

	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt) const
	{
		if (pt.size() != 1) throw std::runtime_error("More or less than one child for implicit tree node.");

		return std::shared_ptr<T>(new T(pt.get_value<T>()));
	}
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<is_base_setting<T>::value>::type>
{
	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
	{
		if (pt.count(key) == 0) return def;
		else if (pt.count(key) > 1) throw std::runtime_error("More than one key found for " + key + ".");

		boost::property_tree::ptree child = pt.get_child(key);
		if (child.size() != 1) throw std::runtime_error("More or less than one child found for pointer (key = " + key + ").");
        return PolymorphicLoader<T>()(child);
	}

	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt) const
	{
		if (pt.size() != 1) throw std::runtime_error("More or less than one child for implicit tree node.");

        return PolymorphicLoader<T>()(pt);
	}
};

struct FileLoader
{
	boost::property_tree::ptree operator () (filesystem::path const& path) const
	{
		if (!exists(path)) throw std::runtime_error("File " + path.string() + " not found.");
		std::ifstream ifs(path.string());
		if (!ifs) throw std::runtime_error("Error opening file " + path.string());
		boost::property_tree::ptree tree;
		if (path.extension() == ".xml") read_xml(ifs, tree);
		else if (path.extension() == ".json") read_json(ifs, tree);
		else throw std::runtime_error("File type " + path.extension().string() + " not known.");
		return tree;
	}
};

} // namespace SettingsDetails
} // namespace BlasBooster

// Initialization list of default constructor
#define MACRO_SINGLE_INITIALIZE_DEFAULT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,2,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_DEFAULT(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_DEFAULT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// Initialization list of parameter constructor
#define MACRO_SINGLE_INITIALIZE_ARGUMENTS(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_ARGUMENTS,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// List of arguments of parameter constructor
#define MACRO_SINGLE_CONSTRUCTOR_ARGUMENT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem) = BOOST_PP_TUPLE_ELEM(3,2,elem) \
	BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CONSTRUCTOR_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_CONSTRUCTOR_ARGUMENT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

// List of arguments of copy constructor
#define MACRO_SINGLE_COPY_ARGUMENTS(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(other. BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_COPY_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_COPY_ARGUMENTS, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// List of arguments for comparison
#define MACRO_SINGLE_COMPARE_ARGUMENTS(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem) == other. BOOST_PP_TUPLE_ELEM(3,1,elem) BOOST_PP_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1),&&,)

#define PRINT_COMPARE_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_COMPARE_ARGUMENTS, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// List of class members
#define MACRO_SINGLE_MEMBER(r,data,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem);

#define PRINT_CLASS_MEMBERS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER,,SEQ)

// List of arguments for loading by boost property tree
#define MACRO_SINGLE_MEMBER_LOAD(r, size, i, elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)( ::BlasBooster::SettingsDetails::GenericLoader<BOOST_PP_TUPLE_ELEM(3,0,elem)>()(tree, \
    BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)), BOOST_PP_TUPLE_ELEM(3,2,elem))) \
	BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CLASS_MEMBERS_LOAD(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_MEMBER_LOAD, BOOST_PP_SEQ_SIZE(SEQ), SEQ)

// Serialization
#define MACRO_SINGLE_MEMBER_SERIALIZATION(r, data, elem) \
    ar & boost::serialization::make_nvp(BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)), BOOST_PP_TUPLE_ELEM(3,1,elem));

#define PRINT_CLASS_MEMBERS_SERIALIZATION(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER_SERIALIZATION,,SEQ)

// Class definition
#define BLASBOOSTER_SETTINGS(Name, Members) \
    struct Name \
    { \
	    typedef bool is_setting; \
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) noexcept \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        Name(Name const& other) noexcept \
         : PRINT_COPY_ARGUMENTS(Members) \
        {} \
\
        Name(boost::property_tree::ptree const& tree) \
         : PRINT_CLASS_MEMBERS_LOAD(Members) \
        {} \
\
		Name(filesystem::path const& path) \
		 : Name( ::BlasBooster::SettingsDetails::FileLoader()(path)) \
		{} \
\
	    virtual ~Name() {}; \
\
        virtual bool operator == (Name const& other) const \
        { \
        	return PRINT_COMPARE_ARGUMENTS(Members); \
        } \
\
        virtual bool operator != (Name const& other) const \
        { \
        	return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
    };

#if 0
    template <> struct BlasBooster::SettingsDetails::is_setting<Name> : std::true_type {}; \
    template <> struct BlasBooster::SettingsDetails::is_base_setting<Name> : std::false_type {};

\
    private:\
\
        friend class boost::serialization::access; \
\
        template <class Archive> \
        void serialize(Archive & ar, const unsigned int version) \
        { \
            PRINT_CLASS_MEMBERS_SERIALIZATION(Members) \
        } \
    }; \
\
    BOOST_CLASS_EXPORT(Name);
#endif
// end macro BLASBOOSTER_SETTINGS

// Base class definition
#define BLASBOOSTER_SETTINGS_BASE(Name, Members, Supplements) \
    struct Name \
    { \
        typedef bool is_setting; \
        typedef bool is_base_setting; \
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) noexcept \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        Name(Name const& other) noexcept \
         : PRINT_COPY_ARGUMENTS(Members) \
        {} \
\
        Name(boost::property_tree::ptree const& tree) \
         : PRINT_CLASS_MEMBERS_LOAD(Members) \
        {} \
\
	    virtual ~Name() {}; \
\
        virtual bool operator == (Name const& other) const \
        { \
        	return PRINT_COMPARE_ARGUMENTS(Members); \
        } \
\
        virtual bool operator != (Name const& other) const \
        { \
        	return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
\
        Supplements \
\
    };

#if 0
    template <> struct BlasBooster::SettingsDetails::is_setting<Name> : std::true_type {}; \
    template <> struct BlasBooster::SettingsDetails::is_base_setting<Name> : std::true_type {};
\
    private:\
\
        friend class boost::serialization::access; \
\
        template <class Archive> \
        void serialize(Archive & ar, const unsigned int version) \
        { \
            PRINT_CLASS_MEMBERS_SERIALIZATION(Members) \
        } \
    }; \
\
    BOOST_CLASS_EXPORT(Name);
#endif
// end macro BLASBOOSTER_SETTINGS_BASE

// Base class definition with no members
// Members must be handled specially, because they can not be empty.
#define BLASBOOSTER_SETTINGS_BASE_NO_MEMBERS(Name, Supplements) \
	struct Name \
	{ \
		typedef bool is_setting; \
		typedef bool is_base_setting; \
\
		virtual ~Name() {}; \
\
		virtual bool operator == (Name const& other) const \
		{ \
			return true; \
		} \
\
		virtual bool operator != (Name const& other) const \
		{ \
			return false; \
		} \
\
		Supplements \
\
	};
// end macro BLASBOOSTER_SETTINGS_BASE

// Derived class definition
#define BLASBOOSTER_SETTINGS_DERIVED(Name, Base, Members, Supplements) \
    struct Name : Base \
    { \
        typedef bool is_setting; \
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) noexcept \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        Name(Name const& other) noexcept \
         : PRINT_COPY_ARGUMENTS(Members) \
        {} \
\
        Name(boost::property_tree::ptree const& tree) \
         : PRINT_CLASS_MEMBERS_LOAD(Members) \
        {} \
\
        virtual ~Name() {}; \
\
        virtual bool operator == (Base const& other) const \
        { \
        	if (!Base::operator == (other)) return false; \
        	return true; \
            /** return PRINT_COMPARE_ARGUMENTS(Members); **/ \
        } \
\
        virtual bool operator != (Base const& other) const \
        { \
        	return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
\
		Supplements \
\
    }; \

#if 0
    template <> struct BlasBooster::SettingsDetails::is_setting<Name> : std::true_type {}; \
    template <> struct BlasBooster::SettingsDetails::is_base_setting<Name> : std::false_type {};

\
    private:\
\
        friend class boost::serialization::access; \
\
        template <class Archive> \
        void serialize(Archive & ar, const unsigned int version) \
        { \
        	boost::serialization::base_object<Base>(*this); \
            PRINT_CLASS_MEMBERS_SERIALIZATION(Members) \
        } \
    }; \
\
    BOOST_CLASS_EXPORT_GUID(Name, BOOST_PP_STRINGIZE(Name));
#endif
// end macro BLASBOOSTER_SETTINGS_DERIVED

// List of derived classes for switch
#define MACRO_SINGLE_CASE_OF_DERIVED_CLASSES(r, Base, Derived) \
    if (pt.front().first == BOOST_PP_STRINGIZE(Derived)) { \
        return std::make_shared<Derived>(pt.front().second); \
    } \
    else
// end macro MACRO_SINGLE_CASE_OF_DERIVED_CLASSES

#define PRINT_CASE_LIST_OF_DERIVED_CLASSES(Base, DerivedList) \
	BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_CASE_OF_DERIVED_CLASSES, Base, DerivedList)
// end macro PRINT_CASE_LIST_OF_DERIVED_CLASSES

// Register for polymorphic classes
#define BLASBOOSTER_SETTINGS_REGISTER(Base, DerivedList) \
	namespace BlasBooster { \
    namespace SettingsDetails { \
    template <> \
    std::shared_ptr<Base> PolymorphicLoader<Base>::operator()(boost::property_tree::ptree const& pt) const \
    { \
	    PRINT_CASE_LIST_OF_DERIVED_CLASSES(Base, DerivedList) \
        throw std::runtime_error("Derived class " + pt.front().first + " not registered for " + BOOST_PP_STRINGIZE(Base) + "."); \
        return std::shared_ptr<Base>(); \
    }}}
// end macro BLASBOOSTER_SETTINGS_REGISTER

#endif // BLASBOOSTER_UTILITIES_SETTINGS_H_
