#ifndef BLASBOOSTER_BLASINTERFACE_BLAS_H_
#define BLASBOOSTER_BLASINTERFACE_BLAS_H_

#include "BlasBoosterMacroBlasFunctionList.h"
#include "BlasBoosterMacroCreateBlasFunctionDeclaration.h"

extern "C" {

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION(BOOST_PP_EMPTY(), BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT)

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION(BOOST_PP_EMPTY(), BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_NO_RETURN)

} // extern "C"

#endif // BLASBOOSTER_BLASINTERFACE_BLAS_H_
