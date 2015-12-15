#ifndef BLASBOOSTER_UTILITIES_SETTINGS_H_
#define BLASBOOSTER_UTILITIES_SETTINGS_H_

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/stringize.hpp>

#define MACRO_SINGLE_INITIALIZE_DEFAULT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,2,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_DEFAULT(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_DEFAULT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_INITIALIZE_ARGUMENTS(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,1,elem)(BOOST_PP_TUPLE_ELEM(3,1,elem)) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_INITIALIZE_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_INITIALIZE_ARGUMENTS,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_CONSTRUCTOR_ARGUMENT(r,size,i,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem) BOOST_PP_COMMA_IF(BOOST_PP_SUB(BOOST_PP_SUB(size,i),1))

#define PRINT_CONSTRUCTOR_ARGUMENTS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(MACRO_SINGLE_CONSTRUCTOR_ARGUMENT,BOOST_PP_SEQ_SIZE(SEQ),SEQ)

#define MACRO_SINGLE_MEMBER(r,data,elem) \
    BOOST_PP_TUPLE_ELEM(3,0,elem) BOOST_PP_TUPLE_ELEM(3,1,elem);

#define PRINT_CLASS_MEMBERS(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER,,SEQ)

#define MACRO_SINGLE_MEMBER_SERIALIZATION(r,data,elem) \
    ar & BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)) & BOOST_PP_TUPLE_ELEM(3,1,elem);

#define PRINT_CLASS_MEMBERS_SERIALIZATION(SEQ) \
    BOOST_PP_SEQ_FOR_EACH(MACRO_SINGLE_MEMBER_SERIALIZATION,,SEQ)

#define BLASBOOSTER_SETTINGS(Name,Members) \
    struct Name \
    { \
        Name() \
         : PRINT_INITIALIZE_DEFAULT(Members) \
        {} \
\
        Name(PRINT_CONSTRUCTOR_ARGUMENTS(Members)) \
         : PRINT_INITIALIZE_ARGUMENTS(Members) \
        {} \
\
        PRINT_CLASS_MEMBERS(Members) \
\
      private: \
\
        template <class Archive> \
        void serialize(Archive & ar, const unsigned int version) \
        { \
            PRINT_CLASS_MEMBERS_SERIALIZATION(Members) \
        } \
\
	    static const bool IsSetting = true; \
    };
// end macro BLASBOOSTER_SETTINGS

#endif // BLASBOOSTER_UTILITIES_SETTINGS_H_
