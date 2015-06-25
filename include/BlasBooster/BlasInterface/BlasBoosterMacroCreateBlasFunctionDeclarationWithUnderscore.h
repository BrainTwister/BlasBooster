#ifndef BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_WITH_UNDERSCORE_H_
#define BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_WITH_UNDERSCORE_H_

#include "BlasBoosterMacroCreateSingleBlasFunctionWithUnderscore.h"
#include "BlasBoosterMacroBlasFunctionList.h"
#include <boost/preprocessor/seq/for_each.hpp>

#define BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_WITH_UNDERSCORE()\
    BOOST_PP_SEQ_FOR_EACH(BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_WITH_UNDERSCORE,,BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST)

#endif /* BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_WITH_UNDERSCORE_H_ */
