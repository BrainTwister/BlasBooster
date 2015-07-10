#include "BlasBooster/BlasInterface/Blas.h"
#include "BlasBooster/BlasInterface/BlasBoosterMacroBlasFunctionList.h"
#include "BlasBooster/BlasInterface/BlasBoosterMacroCreateBlasFunctionDefinitionForInterface.h"
#include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"

extern "C" void openblas_set_num_threads(int nbThreads);

namespace BlasBooster {

void openblas_set_num_threads(int nbThreads)
{
	::openblas_set_num_threads(nbThreads);
}

BLASBOOSTER_MACRO_CREATE_BLAS_FUNCTION_DEFINITION_FOR_INTERFACE(OpenBLAS,BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT)

std::complex<float> BlasInterface < OpenBLAS, cdotc >::operator() (
	const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5 )
{
	std::complex<float> result;
	::cdotc(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<float> BlasInterface < OpenBLAS, cdotu >::operator() (
	const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5 )
{
	std::complex<float> result;
	::cdotu(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<double> BlasInterface < OpenBLAS, zdotc >::operator() (
	const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5 )
{
	std::complex<double> result;
	::zdotc(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<double> BlasInterface < OpenBLAS, zdotu >::operator() (
	const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5 )
{
	std::complex<double> result;
	::zdotu(&result,v1,v2,v3,v4,v5);
	return result;
}

} // namespace BlasBooster
