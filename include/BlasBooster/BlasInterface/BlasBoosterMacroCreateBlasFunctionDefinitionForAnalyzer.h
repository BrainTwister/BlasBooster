#ifndef BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DEFINITION_FOR_ANALYZER_H_
#define BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DEFINITION_FOR_ANALYZER_H_

#include "BlasBoosterMacroBlasFunctionList.h"
#include "BlasBoosterMacroCreateSingleBlasFunctionDefinitionForAnalyzer.h"
#include <boost/preprocessor/seq/for_each.hpp>

#define BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DEFINITION_FOR_ANALYZER()\
    BOOST_PP_SEQ_FOR_EACH(BLASBOOSTER_MACRO_CREATE_SINGLE_BLAS_FUNCTION_DEFINITION_FOR_ANALYZER,,BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST)

#endif /* BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DEFINITION_FOR_ANALYZER_H_ */
