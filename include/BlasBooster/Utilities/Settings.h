#ifndef BLASBOOSTER_UTILITIES_SETTINGS_H_
#define BLASBOOSTER_UTILITIES_SETTINGS_H_

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
#include <boost/property_tree/ptree.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>
#include <iostream>
#include <type_traits>

template <class T, class Enable = void>
struct GenericLoader
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& key, T def) const
	{
    	return pt.get<T>(key, def);
	}
};

template <class T>
struct GenericLoader<std::vector<T>>
{
	std::vector<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::vector<T> def) const
	{
		std::vector<T> r;
		for (auto& item : pt.get_child(key))
			r.push_back(item.second.get_value<T>());
		return r;
	}
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<std::is_fundamental<T>::value>::type>
{
	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
	{
		return std::shared_ptr<T>(new T(pt.get<T>(key)));
	}
};

template <class T>
struct GenericLoader<std::shared_ptr<T>, typename std::enable_if<T::IsBaseSetting>::type>
{
	std::shared_ptr<T> operator () (boost::property_tree::ptree const& pt, std::string const& key, std::shared_ptr<T> def) const
	{
//		std::cout << "1: " << pt.get<std::string>(key) << std::endl;
//		if (pt.count(key) != 1) throw std::runtime_error("More than one key found for " + key + ".");
//		boost::property_tree::ptree child = pt.get_child(key);
//		if (child.size() != 1) throw std::runtime_error("More than one child found for pointer.");
//		std::cout << "2: " << child.get<std::string>() << std::endl;
		return std::shared_ptr<T>();
	}
};

template <class T>
struct GenericLoader<T, typename std::enable_if<T::IsSetting>::type>
{
    T operator () (boost::property_tree::ptree const& pt, std::string const& name, T def) const
	{
        return T(pt.get_child(name));
	}
};

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
    BOOST_PP_TUPLE_ELEM(3,1,elem)(GenericLoader<BOOST_PP_TUPLE_ELEM(3,0,elem)>()(tree, \
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
	    static const bool IsSetting = true; \
	    static const bool IsBaseSetting = false; \
    };

#if 0
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
#define BLASBOOSTER_SETTINGS_BASE(Name, Members) \
    struct Name \
    { \
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
	    static const bool IsSetting = true; \
	    static const bool IsBaseSetting = true; \
    };

#if 0
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

// Derived class definition
#define BLASBOOSTER_SETTINGS_DERIVED(Name, Base, Members) \
    struct Name : Base \
    { \
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
        	return Base::operator == (other) \
                && PRINT_COMPARE_ARGUMENTS(Members); \
        } \
\
        virtual bool operator != (Name const& other) const \
        { \
        	return !operator == (other); \
        } \
\
        PRINT_CLASS_MEMBERS(Members) \
\
	    static const bool IsSetting = true; \
	    static const bool IsBaseSetting = false; \
    };

#if 0
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

#endif // BLASBOOSTER_UTILITIES_SETTINGS_H_
