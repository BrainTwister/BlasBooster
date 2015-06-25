#ifndef BLAS_H_

#include "BlasBoosterMacroBlasFunctionList.h"
#include "BlasBoosterMacroCreateBlasFunctionDeclaration.h"

extern "C" {

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION(BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT)

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION(BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_NO_RETURN)

} // extern "C"

#endif /* BLAS_H_ */
