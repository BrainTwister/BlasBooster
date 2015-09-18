#ifndef BLASINTERFACE_INTELMKL_H_
#define BLASINTERFACE_INTELMKL_H_

#include "BlasBooster/BlasInterface/BlasBoosterMacroBlasFunctionList.h"
#include "BlasBooster/BlasInterface/BlasBoosterMacroCreateBlasFunctionDeclarationForInterface.h"
#include "BlasBooster/BlasInterface/BlasBoosterMacroSpBlasFunctionList.h"
#include "BlasBooster/BlasInterface/BlasFunctionType.h"
#include "BlasBooster/BlasInterface/BlasInterface.h"

namespace BlasBooster {

struct IntelMKL {};

void mkl_set_num_threads(int nbThreads);

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE( IntelMKL, BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT )

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE( IntelMKL, BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_WITH_RETURN )

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DECLARATION_FOR_INTERFACE( IntelMKL, BLASBOOSTER_MACRO_SPBLAS_FUNCTION_LIST )

} // namespace BlasBooster

#endif // BLASINTERFACE_INTELMKL_H_
