#ifndef BLASINTERFACE_OPENBLAS_H_
#define BLASINTERFACE_OPENBLAS_H_

#include "BlasBoosterMacroBlasFunctionList.h"
#include "BlasBoosterMacroCreateBlasFunctionDeclarationForInterface.h"
#include "BlasInterface.h"
#include "BlasFunctionType.h"

namespace BlasBooster {

struct OpenBLAS {};

void openblas_set_num_threads(int nbThreads);

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE(OpenBLAS, BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT)

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE(OpenBLAS, BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_WITH_RETURN)

} // namespace BlasBooster

#endif /* BLASINTERFACE_OPENBLAS_H_ */
