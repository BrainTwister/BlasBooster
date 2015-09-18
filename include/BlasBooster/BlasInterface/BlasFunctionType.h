#ifndef BLASFUNCTIONTYPE_H_
#define BLASFUNCTIONTYPE_H_

#include "BlasBoosterMacroBlasFunctionList.h"
#include "BlasBoosterMacroSpBlasFunctionList.h"
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <string>

#define BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE(r,data,elem)\
    struct BOOST_PP_TUPLE_ELEM(3,1,elem) {\
        static std::string name() { return BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_ELEM(3,1,elem)); }\
    };

#define BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_TYPE()\
    BOOST_PP_SEQ_FOR_EACH(BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE,,BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST)\
    BOOST_PP_SEQ_FOR_EACH(BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_TYPE,,BLASBOOSTER_MACRO_SPBLAS_FUNCTION_LIST)

namespace BlasBooster {

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_TYPE()

} // namespace BlasBooster

#endif // BLASFUNCTIONTYPE_H_
