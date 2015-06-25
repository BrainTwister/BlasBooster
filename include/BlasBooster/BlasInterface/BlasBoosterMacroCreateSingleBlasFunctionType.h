#ifndef BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE_H_
#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE_H_

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <string>

#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE(r,data,elem)\
    struct BOOST_PP_TUPLE_ELEM(3,1,elem) {\
        static std::string name() { return BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)); }\
    };

#endif /* BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE_H_ */
