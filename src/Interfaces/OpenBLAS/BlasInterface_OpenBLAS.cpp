#include "BlasBooster/BlasInterface/Blas.h"
#include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"

extern "C" void openblas_set_num_threads(int nbThreads);

namespace BlasBooster {

void OpenBLAS_set_num_threads(int nbThreads)
{
    ::openblas_set_num_threads(nbThreads);
}

float BlasInterface <OpenBLAS, scabs1>::operator() (
    const std::complex<float>* v0) const
{
    return ::scabs1_(v0);
}

float BlasInterface <OpenBLAS, sasum>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::sasum_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, saxpy>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, float* v4, const int* v5) const
{
    return ::saxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, saxpby>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::saxpby_(v0, v1, v2, v3, v4, v5, v6);
}

float BlasInterface <OpenBLAS, scasum>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::scasum_(v0, v1, v2);
}

float BlasInterface <OpenBLAS, scnrm2>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::scnrm2_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, scopy>::operator() (
    const int* v0, const float* v1, const int* v2, float* v3, const int* v4) const
{
    return ::scopy_(v0, v1, v2, v3, v4);
}

float BlasInterface <OpenBLAS, sdot>::operator() (
    const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const
{
    return ::sdot_(v0, v1, v2, v3, v4);
}

float BlasInterface <OpenBLAS, sdsdot>::operator() (
    const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, const int* v5) const
{
    return ::sdsdot_(v0, v1, v2, v3, v4, v5);
}

float BlasInterface <OpenBLAS, snrm2>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::snrm2_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, srot>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5, const float* v6) const
{
    return ::srot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, srotg>::operator() (
    float* v0, float* v1, float* v2, float* v3) const
{
    return ::srotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, srotm>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5) const
{
    return ::srotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, srotmg>::operator() (
    float* v0, float* v1, float* v2, const float* v3, float* v4) const
{
    return ::srotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBLAS, sscal>::operator() (
    const int* v0, const float* v1, float* v2, const int* v3) const
{
    return ::sscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, sswap>::operator() (
    const int* v0, float* v1, const int* v2, float* v3, const int* v4) const
{
    return ::sswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBLAS, isamax>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::isamax_(v0, v1, v2);
}

int BlasInterface <OpenBLAS, isamin>::operator() (
    const int* v0, const float* v1, const int* v2) const
{
    return ::isamin_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, caxpy>::operator() (
    const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, std::complex<float>* v4, const int* v5) const
{
    return ::caxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, caxpby>::operator() (
    const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::caxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ccopy>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const
{
    return ::ccopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBLAS, crotg>::operator() (
    std::complex<float>* v0, const std::complex<float>* v1, float* v2, std::complex<float>* v3) const
{
    return ::crotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, cscal>::operator() (
    const int* v0, const std::complex<float>* v1, std::complex<float>* v2, const int* v3) const
{
    return ::cscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, csrot>::operator() (
    const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4, const float* v5, const float* v6) const
{
    return ::csrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, csscal>::operator() (
    const int* v0, const float* v1, std::complex<float>* v2, const int* v3) const
{
    return ::csscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, cswap>::operator() (
    const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const
{
    return ::cswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBLAS, icamax>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::icamax_(v0, v1, v2);
}

int BlasInterface <OpenBLAS, icamin>::operator() (
    const int* v0, const std::complex<float>* v1, const int* v2) const
{
    return ::icamin_(v0, v1, v2);
}

double BlasInterface <OpenBLAS, dcabs1>::operator() (
    const std::complex<double>* v0) const
{
    return ::dcabs1_(v0);
}

double BlasInterface <OpenBLAS, dasum>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::dasum_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, daxpy>::operator() (
    const int* v0, const double* v1, const double* v2, const int* v3, double* v4, const int* v5) const
{
    return ::daxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, daxpby>::operator() (
    const int* v0, const double* v1, const double* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::daxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, dcopy>::operator() (
    const int* v0, const double* v1, const int* v2, double* v3, const int* v4) const
{
    return ::dcopy_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBLAS, ddot>::operator() (
    const int* v0, const double* v1, const int* v2, const double* v3, const int* v4) const
{
    return ::ddot_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBLAS, dsdot>::operator() (
    const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const
{
    return ::dsdot_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBLAS, dnrm2>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::dnrm2_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, drot>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5, const double* v6) const
{
    return ::drot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, drotg>::operator() (
    double* v0, double* v1, double* v2, double* v3) const
{
    return ::drotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, drotm>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5) const
{
    return ::drotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, drotmg>::operator() (
    double* v0, double* v1, double* v2, const double* v3, double* v4) const
{
    return ::drotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBLAS, dscal>::operator() (
    const int* v0, const double* v1, double* v2, const int* v3) const
{
    return ::dscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, dswap>::operator() (
    const int* v0, double* v1, const int* v2, double* v3, const int* v4) const
{
    return ::dswap_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBLAS, dzasum>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::dzasum_(v0, v1, v2);
}

double BlasInterface <OpenBLAS, dznrm2>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::dznrm2_(v0, v1, v2);
}

int BlasInterface <OpenBLAS, idamax>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::idamax_(v0, v1, v2);
}

int BlasInterface <OpenBLAS, idamin>::operator() (
    const int* v0, const double* v1, const int* v2) const
{
    return ::idamin_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, zaxpy>::operator() (
    const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, std::complex<double>* v4, const int* v5) const
{
    return ::zaxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, zaxpby>::operator() (
    const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::zaxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, zcopy>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const
{
    return ::zcopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBLAS, zdrot>::operator() (
    const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4, const double* v5, const double* v6) const
{
    return ::zdrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, zdscal>::operator() (
    const int* v0, const double* v1, std::complex<double>* v2, const int* v3) const
{
    return ::zdscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, zrotg>::operator() (
    std::complex<double>* v0, const std::complex<double>* v1, double* v2, std::complex<double>* v3) const
{
    return ::zrotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, zscal>::operator() (
    const int* v0, const std::complex<double>* v1, std::complex<double>* v2, const int* v3) const
{
    return ::zscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBLAS, zswap>::operator() (
    const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const
{
    return ::zswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBLAS, izamax>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::izamax_(v0, v1, v2);
}

int BlasInterface <OpenBLAS, izamin>::operator() (
    const int* v0, const std::complex<double>* v1, const int* v2) const
{
    return ::izamin_(v0, v1, v2);
}

void BlasInterface <OpenBLAS, sgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const
{
    return ::sgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, sgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const
{
    return ::sgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, sger>::operator() (
    const int* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::sger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, ssbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const
{
    return ::ssbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, sspmv>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const float* v4, const int* v5, const float* v6, float* v7, const int* v8) const
{
    return ::sspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, sspr>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5) const
{
    return ::sspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, sspr2>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7) const
{
    return ::sspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, ssymv>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const
{
    return ::ssymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, ssyr>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5, const int* v6) const
{
    return ::ssyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ssyr2>::operator() (
    const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::ssyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, stbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::stbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, stbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const
{
    return ::stbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, stpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::stpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, stpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const
{
    return ::stpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, strmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const
{
    return ::strmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, strsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const
{
    return ::strsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, cgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, cgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const
{
    return ::cgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, cgerc>::operator() (
    const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, cgeru>::operator() (
    const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, chbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const
{
    return ::chbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, chemv>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const
{
    return ::chemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, cher>::operator() (
    const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5, const int* v6) const
{
    return ::cher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, cher2>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::cher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, chpmv>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, std::complex<float>* v7, const int* v8) const
{
    return ::chpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, chpr>::operator() (
    const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5) const
{
    return ::chpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, chpr2>::operator() (
    const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7) const
{
    return ::chpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, ctbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::ctbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, ctbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const
{
    return ::ctbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, ctpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::ctpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ctpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const
{
    return ::ctpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ctrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const
{
    return ::ctrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, ctrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const
{
    return ::ctrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, dgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const
{
    return ::dgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, dgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const
{
    return ::dgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, dger>::operator() (
    const int* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, dsbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const
{
    return ::dsbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, dspmv>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const double* v4, const int* v5, const double* v6, double* v7, const int* v8) const
{
    return ::dspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, dspr>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5) const
{
    return ::dspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, dspr2>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7) const
{
    return ::dspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, dsymv>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const
{
    return ::dsymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, dsyr>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5, const int* v6) const
{
    return ::dsyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, dsyr2>::operator() (
    const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dsyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, dtbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dtbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, dtbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const
{
    return ::dtbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, dtpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::dtpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, dtpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const
{
    return ::dtpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, dtrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const
{
    return ::dtrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, dtrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const
{
    return ::dtrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, zgbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, zgemv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const
{
    return ::zgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, zgerc>::operator() (
    const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, zgeru>::operator() (
    const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, zhbmv>::operator() (
    const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const
{
    return ::zhbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, zhemv>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zhemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, zher>::operator() (
    const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5, const int* v6) const
{
    return ::zher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, zher2>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, zhpmv>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, std::complex<double>* v7, const int* v8) const
{
    return ::zhpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, zhpr>::operator() (
    const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5) const
{
    return ::zhpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBLAS, zhpr2>::operator() (
    const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7) const
{
    return ::zhpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, ztbmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::ztbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, ztbsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const
{
    return ::ztbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBLAS, ztpmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::ztpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ztpsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const
{
    return ::ztpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBLAS, ztrmv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const
{
    return ::ztrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, ztrsv>::operator() (
    const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const
{
    return ::ztrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBLAS, sgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const
{
    return ::sgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, ssymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const
{
    return ::ssymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, ssyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const
{
    return ::ssyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, ssyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const
{
    return ::ssyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, strmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const
{
    return ::strmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, strsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const
{
    return ::strsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, cgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, cgemm3m>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const
{
    return ::cgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, chemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::chemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, cher2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const float* v9, std::complex<float>* v10, const int* v11) const
{
    return ::cher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, cherk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const std::complex<float>* v5, const int* v6, const float* v7, std::complex<float>* v8, const int* v9) const
{
    return ::cherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, csymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::csymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, csyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const
{
    return ::csyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, csyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const
{
    return ::csyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, ctrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const
{
    return ::ctrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, ctrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const
{
    return ::ctrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, dgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const
{
    return ::dgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, dsymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const
{
    return ::dsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, dsyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const
{
    return ::dsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, dsyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const
{
    return ::dsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, dtrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const
{
    return ::dtrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, dtrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const
{
    return ::dtrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, zgemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, zgemm3m>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const
{
    return ::zgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBLAS, zhemm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zhemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, zher2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const double* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, zherk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const std::complex<double>* v5, const int* v6, const double* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, zsymm>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, zsyr2k>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const
{
    return ::zsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBLAS, zsyrk>::operator() (
    const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const
{
    return ::zsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBLAS, ztrmm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const
{
    return ::ztrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBLAS, ztrsm>::operator() (
    const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const
{
    return ::ztrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

std::complex<float> BlasInterface < OpenBLAS, cdotc >::operator() (
    const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5) const
{
    std::complex<float> result;
    ::cdotc_(&result,v1,v2,v3,v4,v5);
    return result;
}

std::complex<float> BlasInterface < OpenBLAS, cdotu >::operator() (
    const int *v1, const std::complex<float> *v2, const int *v3, const std::complex<float> *v4, const int *v5) const
{
    std::complex<float> result;
    ::cdotu_(&result,v1,v2,v3,v4,v5);
    return result;
}

std::complex<double> BlasInterface < OpenBLAS, zdotc >::operator() (
    const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5) const
{
    std::complex<double> result;
    ::zdotc_(&result,v1,v2,v3,v4,v5);
    return result;
}

std::complex<double> BlasInterface < OpenBLAS, zdotu >::operator() (
    const int *v1, const std::complex<double> *v2, const int *v3, const std::complex<double> *v4, const int *v5) const
{
    std::complex<double> result;
    ::zdotu_(&result,v1,v2,v3,v4,v5);
    return result;
}

} // namespace BlasBooster