#include "BlasBooster/BlasInterface/Blas.h"
#include "BlasBooster/BlasInterface/IntelMKL_SpBlas.h"
#include "BlasBooster/BlasInterface/BlasInterface_IntelMKL.h"

// The upper case name must be used, since the lower case one is
// only a macro defined in mkl_service.h and results in a seg-fault.
extern "C" {
    void MKL_Set_Dynamic (int flag);
    void MKL_Set_Num_Threads(int nbThreads);
}

namespace BlasBooster {

void IntelMKL_set_num_threads(int nbThreads)
{
	::MKL_Set_Dynamic(0);
	::MKL_Set_Num_Threads(nbThreads);
}

float BlasInterface <IntelMKL, scabs1>::operator() (
    const std::complex<float>* v0) const
{
    return ::scabs1_(v0);
}

float BlasInterface <IntelMKL, sasum>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::sasum_(v0, v1, v2);
}

void BlasInterface <IntelMKL, saxpy>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, float* v4, const int* v5) const
{
    return ::saxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, saxpby>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::saxpby_(v0, v1, v2, v3, v4, v5, v6);
}

float BlasInterface <IntelMKL, scasum>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::scasum_(v0, v1, v2);
}

float BlasInterface <IntelMKL, scnrm2>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::scnrm2_(v0, v1, v2);
}

void BlasInterface <IntelMKL, scopy>::operator() (
    const int* v0, const float* v1, const int* v2, float* v3, const int* v4) const
{
    return ::scopy_(v0, v1, v2, v3, v4);
}

float BlasInterface <IntelMKL, sdot>::operator() (
    const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const
{
    return ::sdot_(v0, v1, v2, v3, v4);
}

float BlasInterface <IntelMKL, sdsdot>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, const int* v5) const
{
    return ::sdsdot_(v0, v1, v2, v3, v4, v5);
}

float BlasInterface <IntelMKL, snrm2>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::snrm2_(v0, v1, v2);
}

void BlasInterface <IntelMKL, srot>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5, const float* v6) const
{
    return ::srot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, srotg>::operator() (
    float* v0, float* v1, float* v2, float* v3) const
{
    return ::srotg_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, srotm>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5) const
{
    return ::srotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, srotmg>::operator() (
    float* v0, float* v1, float* v2, const float* v3, float* v4) const
{
    return ::srotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <IntelMKL, sscal>::operator() (
    const int* v0, const float* v1, float* v2, const int* v3) const
{
    return ::sscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, sswap>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4) const
{
    return ::sswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <IntelMKL, isamax>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::isamax_(v0, v1, v2);
}

int BlasInterface <IntelMKL, isamin>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::isamin_(v0, v1, v2);
}

void BlasInterface <IntelMKL, caxpy>::operator() (
    const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, std::complex<float>* v4, const int* v5) const
{
    return ::caxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, caxpby>::operator() (
    const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::caxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ccopy>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const
{
    return ::ccopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <IntelMKL, crotg>::operator() (
    std::complex<float>* v0, const std::complex<float>* v1, float* v2, std::complex<float>* v3) const
{
    return ::crotg_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, cscal>::operator() (
    const int* v0, const std::complex<float>* v1, std::complex<float>* v2, const int* v3) const
{
    return ::cscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, csrot>::operator() (
    const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4, const float* v5, const float* v6) const
{
    return ::csrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, csscal>::operator() (
    const int* v0, const float* v1, std::complex<float>* v2, const int* v3) const
{
    return ::csscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, cswap>::operator() (
    const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const
{
    return ::cswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <IntelMKL, icamax>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::icamax_(v0, v1, v2);
}

int BlasInterface <IntelMKL, icamin>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::icamin_(v0, v1, v2);
}

double BlasInterface <IntelMKL, dcabs1>::operator() (
    const std::complex<double>* v0) const
{
    return ::dcabs1_(v0);
}

double BlasInterface <IntelMKL, dasum>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::dasum_(v0, v1, v2);
}

void BlasInterface <IntelMKL, daxpy>::operator() (
    const int* v0, const double* v1, const double* v2, const int* v3, double* v4, const int* v5) const
{
    return ::daxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, daxpby>::operator() (
    const int* v0, const double* v1, const double* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::daxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, dcopy>::operator() (
    const int* v0, const double* v1, const int* v2, double* v3, const int* v4) const
{
    return ::dcopy_(v0, v1, v2, v3, v4);
}

double BlasInterface <IntelMKL, ddot>::operator() (
    const int* v0, const double* v1, const int* v2, const double* v3, const int* v4) const
{
    return ::ddot_(v0, v1, v2, v3, v4);
}

double BlasInterface <IntelMKL, dsdot>::operator() (
    const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const
{
    return ::dsdot_(v0, v1, v2, v3, v4);
}

double BlasInterface <IntelMKL, dnrm2>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::dnrm2_(v0, v1, v2);
}

void BlasInterface <IntelMKL, drot>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5, const double* v6) const
{
    return ::drot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, drotg>::operator() (
    double* v0, double* v1, double* v2, double* v3) const
{
    return ::drotg_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, drotm>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5) const
{
    return ::drotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, drotmg>::operator() (
    double* v0, double* v1, double* v2, const double* v3, double* v4) const
{
    return ::drotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <IntelMKL, dscal>::operator() (
    const int* v0, const double* v1, double* v2, const int* v3) const
{
    return ::dscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, dswap>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4) const
{
    return ::dswap_(v0, v1, v2, v3, v4);
}

double BlasInterface <IntelMKL, dzasum>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::dzasum_(v0, v1, v2);
}

double BlasInterface <IntelMKL, dznrm2>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::dznrm2_(v0, v1, v2);
}

int BlasInterface <IntelMKL, idamax>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::idamax_(v0, v1, v2);
}

int BlasInterface <IntelMKL, idamin>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::idamin_(v0, v1, v2);
}

void BlasInterface <IntelMKL, zaxpy>::operator() (
    const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, std::complex<double>* v4, const int* v5) const
{
    return ::zaxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, zaxpby>::operator() (
    const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::zaxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, zcopy>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const
{
    return ::zcopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <IntelMKL, zdrot>::operator() (
    const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4, const double* v5, const double* v6) const
{
    return ::zdrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, zdscal>::operator() (
    const int* v0, const double* v1, std::complex<double>* v2, const int* v3) const
{
    return ::zdscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, zrotg>::operator() (
    std::complex<double>* v0, const std::complex<double>* v1, double* v2, std::complex<double>* v3) const
{
    return ::zrotg_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, zscal>::operator() (
    const int* v0, const std::complex<double>* v1, std::complex<double>* v2, const int* v3) const
{
    return ::zscal_(v0, v1, v2, v3);
}

void BlasInterface <IntelMKL, zswap>::operator() (
    const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const
{
    return ::zswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <IntelMKL, izamax>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::izamax_(v0, v1, v2);
}

int BlasInterface <IntelMKL, izamin>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::izamin_(v0, v1, v2);
}

void BlasInterface <IntelMKL, sgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const
{
    return ::sgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, sgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const
{
    return ::sgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, sger>::operator() (
    const int* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::sger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, ssbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const
{
    return ::ssbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, sspmv>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const float* v4, const int* v5, const float* v6, float* v7, const int* v8) const
{
    return ::sspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, sspr>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5) const
{
    return ::sspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, sspr2>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7) const
{
    return ::sspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, ssymv>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const
{
    return ::ssymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, ssyr>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5, const int* v6) const
{
    return ::ssyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ssyr2>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::ssyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, stbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::stbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, stbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::stbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, stpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::stpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, stpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::stpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, strmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const
{
    return ::strmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, strsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const
{
    return ::strsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, cgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, cgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const
{
    return ::cgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, cgerc>::operator() (
    const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, cgeru>::operator() (
    const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, chbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const
{
    return ::chbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, chemv>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const
{
    return ::chemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, cher>::operator() (
    const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5, const int* v6) const
{
    return ::cher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, cher2>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, chpmv>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, std::complex<float>* v7, const int* v8) const
{
    return ::chpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, chpr>::operator() (
    const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5) const
{
    return ::chpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, chpr2>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7) const
{
    return ::chpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, ctbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::ctbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, ctbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::ctbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, ctpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::ctpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ctpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::ctpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ctrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const
{
    return ::ctrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, ctrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const
{
    return ::ctrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, dgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const
{
    return ::dgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, dgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const
{
    return ::dgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, dger>::operator() (
    const int* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, dsbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const
{
    return ::dsbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, dspmv>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const double* v4, const int* v5, const double* v6, double* v7, const int* v8) const
{
    return ::dspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, dspr>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5) const
{
    return ::dspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, dspr2>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7) const
{
    return ::dspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, dsymv>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const
{
    return ::dsymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, dsyr>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5, const int* v6) const
{
    return ::dsyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, dsyr2>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dsyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, dtbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dtbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, dtbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dtbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, dtpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::dtpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, dtpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::dtpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, dtrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const
{
    return ::dtrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, dtrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const
{
    return ::dtrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, zgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, zgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const
{
    return ::zgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, zgerc>::operator() (
    const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, zgeru>::operator() (
    const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, zhbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const
{
    return ::zhbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, zhemv>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zhemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, zher>::operator() (
    const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5, const int* v6) const
{
    return ::zher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, zher2>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, zhpmv>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zhpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, zhpr>::operator() (
    const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5) const
{
    return ::zhpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <IntelMKL, zhpr2>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7) const
{
    return ::zhpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, ztbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::ztbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, ztbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::ztbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <IntelMKL, ztpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::ztpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ztpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::ztpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <IntelMKL, ztrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const
{
    return ::ztrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, ztrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const
{
    return ::ztrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <IntelMKL, sgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const
{
    return ::sgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, ssymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const
{
    return ::ssymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, ssyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const
{
    return ::ssyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, ssyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const
{
    return ::ssyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, strmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const
{
    return ::strmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, strsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const
{
    return ::strsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, cgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, cgemm3m>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, chemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::chemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, cher2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const float* v9, std::complex<float>* v10, const int* v11) const
{
    return ::cher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, cherk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const std::complex<float>* v5, const int* v6, const float* v7, std::complex<float>* v8, const int* v9) const
{
    return ::cherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, csymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::csymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, csyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::csyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, csyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const
{
    return ::csyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, ctrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const
{
    return ::ctrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, ctrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const
{
    return ::ctrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, dgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const
{
    return ::dgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, dsymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const
{
    return ::dsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, dsyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const
{
    return ::dsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, dsyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const
{
    return ::dsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, dtrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const
{
    return ::dtrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, dtrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const
{
    return ::dtrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, zgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, zgemm3m>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <IntelMKL, zhemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zhemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, zher2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const double* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, zherk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const std::complex<double>* v5, const int* v6, const double* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, zsymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, zsyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <IntelMKL, zsyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <IntelMKL, ztrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const
{
    return ::ztrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, ztrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const
{
    return ::ztrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <IntelMKL, dcsrmm>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const double* v4, const char* v5, const double* v6, const int* v7, const int* v8, const int* v9, const double* v10, const int* v11, const double* v12, double* v13, const int* v14) const
{
    return ::mkl_dcsrmm(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
}

void BlasInterface <IntelMKL, dcsrmultcsr>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const int* v5, double* v6, int* v7, int* v8, double* v9, int* v10, int* v11, double* v12, int* v13, int* v14, const int* v15, int* v16) const
{
    return ::mkl_dcsrmultcsr(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
}

void BlasInterface <IntelMKL, scsrmm>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const float* v4, const char* v5, const float* v6, const int* v7, const int* v8, const int* v9, const float* v10, const int* v11, const float* v12, float* v13, const int* v14) const
{
    return ::mkl_scsrmm(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14);
}

void BlasInterface <IntelMKL, scsrmultcsr>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const int* v5, float* v6, int* v7, int* v8, float* v9, int* v10, int* v11, float* v12, int* v13, int* v14, const int* v15, int* v16) const
{
    return ::mkl_scsrmultcsr(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16);
}

std::complex<float> BlasInterface<IntelMKL, cdotc>::operator() (
	const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5 ) const
{
	std::complex<float> result;
	::cdotc_(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<float> BlasInterface<IntelMKL, cdotu>::operator() (
	const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5 ) const
{
	std::complex<float> result;
	::cdotu_(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<double> BlasInterface<IntelMKL, zdotc>::operator() (
	const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5 ) const
{
	std::complex<double> result;
	::zdotc_(&result,v1,v2,v3,v4,v5);
	return result;
}

std::complex<double> BlasInterface<IntelMKL, zdotu>::operator() (
	const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5 ) const
{
	std::complex<double> result;
	::zdotu_(&result,v1,v2,v3,v4,v5);
	return result;
}

} // namespace BlasBooster
