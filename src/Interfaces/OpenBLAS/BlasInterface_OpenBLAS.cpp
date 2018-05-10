#include "BlasBooster/BlasInterface/Blas.h"
#include "BlasBooster/BlasInterface/BlasInterface_OpenBLAS.h"

extern "C" void openblas_set_num_threads(int nbThreads);

namespace BlasBooster {

void openblas_set_num_threads(int nbThreads)
{
    ::openblas_set_num_threads(nbThreads);
}

float BlasInterface <OpenBlas, scabs1>::operator() (
    const std::complex<float> v0) const
{
    return ::scabs1_(v0);
}

float BlasInterface <OpenBlas, sasum>::operator() (
    const int v0, const float v1, const int v2) const
{
    return ::sasum_(v0, v1, v2);
}

void BlasInterface <OpenBlas, saxpy>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4, const int v5) const
{
    return ::saxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, saxpby>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, float v5, const int v6) const
{
    return ::saxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, saxpyi>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4) const
{
    return ::saxpyi_(v0, v1, v2, v3, v4);
}

float BlasInterface <OpenBlas, scasum>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const
{
    return ::scasum_(v0, v1, v2);
}

float BlasInterface <OpenBlas, scnrm2>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const
{
    return ::scnrm2_(v0, v1, v2);
}

void BlasInterface <OpenBlas, scopy>::operator() (
    const int v0, const float v1, const int v2, float v3, const int v4) const
{
    return ::scopy_(v0, v1, v2, v3, v4);
}

float BlasInterface <OpenBlas, sdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const
{
    return ::sdot_(v0, v1, v2, v3, v4);
}

float BlasInterface <OpenBlas, sdoti>::operator() (
    const int v0, const float v1, const int v2, const float v3) const
{
    return ::sdoti_(v0, v1, v2, v3);
}

float BlasInterface <OpenBlas, sdsdot>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, const int v5) const
{
    return ::sdsdot_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, sgthr>::operator() (
    const int v0, const float v1, float v2, const int v3) const
{
    return ::sgthr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, sgthrz>::operator() (
    const int v0, float v1, float v2, const int v3) const
{
    return ::sgthrz_(v0, v1, v2, v3);
}

float BlasInterface <OpenBlas, snrm2>::operator() (
    const int v0, const float v1, const int v2) const
{
    return ::snrm2_(v0, v1, v2);
}

void BlasInterface <OpenBlas, srot>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5, const float v6) const
{
    return ::srot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, srotg>::operator() (
    float v0, float v1, float v2, float v3) const
{
    return ::srotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, sroti>::operator() (
    const int v0, float v1, const int v2, float v3, const float v4, const float v5) const
{
    return ::sroti_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, srotm>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5) const
{
    return ::srotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, srotmg>::operator() (
    float v0, float v1, float v2, const float v3, float v4) const
{
    return ::srotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, sscal>::operator() (
    const int v0, const float v1, float v2, const int v3) const
{
    return ::sscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, ssctr>::operator() (
    const int v0, const float v1, const int v2, float v3) const
{
    return ::ssctr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, sswap>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4) const
{
    return ::sswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBlas, isamax>::operator() (
    const int v0, const float v1, const int v2) const
{
    return ::isamax_(v0, v1, v2);
}

int BlasInterface <OpenBlas, isamin>::operator() (
    const int v0, const float v1, const int v2) const
{
    return ::isamin_(v0, v1, v2);
}

void BlasInterface <OpenBlas, caxpy>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4, const int v5) const
{
    return ::caxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, caxpby>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const
{
    return ::caxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, caxpyi>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4) const
{
    return ::caxpyi_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, ccopy>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const
{
    return ::ccopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, cgthr>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const
{
    return ::cgthr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, cgthrz>::operator() (
    const int v0, std::complex<float> v1, std::complex<float> v2, const int v3) const
{
    return ::cgthrz_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, crotg>::operator() (
    std::complex<float> v0, const std::complex<float> v1, float v2, std::complex<float> v3) const
{
    return ::crotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, cscal>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const
{
    return ::cscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, csctr>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3) const
{
    return ::csctr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, csrot>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4, const float v5, const float v6) const
{
    return ::csrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, csscal>::operator() (
    const int v0, const float v1, std::complex<float> v2, const int v3) const
{
    return ::csscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, cswap>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const
{
    return ::cswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBlas, icamax>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const
{
    return ::icamax_(v0, v1, v2);
}

int BlasInterface <OpenBlas, icamin>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const
{
    return ::icamin_(v0, v1, v2);
}

double BlasInterface <OpenBlas, dcabs1>::operator() (
    const std::complex<double> v0) const
{
    return ::dcabs1_(v0);
}

double BlasInterface <OpenBlas, dasum>::operator() (
    const int v0, const double v1, const int v2) const
{
    return ::dasum_(v0, v1, v2);
}

void BlasInterface <OpenBlas, daxpy>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4, const int v5) const
{
    return ::daxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, daxpby>::operator() (
    const int v0, const double v1, const double v2, const int v3, const double v4, double v5, const int v6) const
{
    return ::daxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, daxpyi>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4) const
{
    return ::daxpyi_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, dcopy>::operator() (
    const int v0, const double v1, const int v2, double v3, const int v4) const
{
    return ::dcopy_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBlas, ddot>::operator() (
    const int v0, const double v1, const int v2, const double v3, const int v4) const
{
    return ::ddot_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBlas, dsdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const
{
    return ::dsdot_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBlas, ddoti>::operator() (
    const int v0, const double v1, const int v2, const double v3) const
{
    return ::ddoti_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, dgthr>::operator() (
    const int v0, const double v1, double v2, const int v3) const
{
    return ::dgthr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, dgthrz>::operator() (
    const int v0, double v1, double v2, const int v3) const
{
    return ::dgthrz_(v0, v1, v2, v3);
}

double BlasInterface <OpenBlas, dnrm2>::operator() (
    const int v0, const double v1, const int v2) const
{
    return ::dnrm2_(v0, v1, v2);
}

void BlasInterface <OpenBlas, drot>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5, const double v6) const
{
    return ::drot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, drotg>::operator() (
    double v0, double v1, double v2, double v3) const
{
    return ::drotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, droti>::operator() (
    const int v0, double v1, const int v2, double v3, const double v4, const double v5) const
{
    return ::droti_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, drotm>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5) const
{
    return ::drotm_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, drotmg>::operator() (
    double v0, double v1, double v2, const double v3, double v4) const
{
    return ::drotmg_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, dscal>::operator() (
    const int v0, const double v1, double v2, const int v3) const
{
    return ::dscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, dsctr>::operator() (
    const int v0, const double v1, const int v2, double v3) const
{
    return ::dsctr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, dswap>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4) const
{
    return ::dswap_(v0, v1, v2, v3, v4);
}

double BlasInterface <OpenBlas, dzasum>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const
{
    return ::dzasum_(v0, v1, v2);
}

double BlasInterface <OpenBlas, dznrm2>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const
{
    return ::dznrm2_(v0, v1, v2);
}

int BlasInterface <OpenBlas, idamax>::operator() (
    const int v0, const double v1, const int v2) const
{
    return ::idamax_(v0, v1, v2);
}

int BlasInterface <OpenBlas, idamin>::operator() (
    const int v0, const double v1, const int v2) const
{
    return ::idamin_(v0, v1, v2);
}

void BlasInterface <OpenBlas, zaxpy>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4, const int v5) const
{
    return ::zaxpy_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, zaxpby>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const
{
    return ::zaxpby_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, zaxpyi>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4) const
{
    return ::zaxpyi_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, zcopy>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const
{
    return ::zcopy_(v0, v1, v2, v3, v4);
}

void BlasInterface <OpenBlas, zdrot>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4, const double v5, const double v6) const
{
    return ::zdrot_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, zdscal>::operator() (
    const int v0, const double v1, std::complex<double> v2, const int v3) const
{
    return ::zdscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zgthr>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const
{
    return ::zgthr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zgthrz>::operator() (
    const int v0, std::complex<double> v1, std::complex<double> v2, const int v3) const
{
    return ::zgthrz_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zrotg>::operator() (
    std::complex<double> v0, const std::complex<double> v1, double v2, std::complex<double> v3) const
{
    return ::zrotg_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zscal>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const
{
    return ::zscal_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zsctr>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3) const
{
    return ::zsctr_(v0, v1, v2, v3);
}

void BlasInterface <OpenBlas, zswap>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const
{
    return ::zswap_(v0, v1, v2, v3, v4);
}

int BlasInterface <OpenBlas, izamax>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const
{
    return ::izamax_(v0, v1, v2);
}

int BlasInterface <OpenBlas, izamin>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const
{
    return ::izamin_(v0, v1, v2);
}

void BlasInterface <OpenBlas, sgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const
{
    return ::sgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, sgemv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const
{
    return ::sgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, sger>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const
{
    return ::sger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, ssbmv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const
{
    return ::ssbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, sspmv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const float v4, const int v5, const float v6, float v7, const int v8) const
{
    return ::sspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, sspr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5) const
{
    return ::sspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, sspr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7) const
{
    return ::sspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, ssymv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, float v8, const int v9) const
{
    return ::ssymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, ssyr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5, const int v6) const
{
    return ::ssyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, ssyr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const
{
    return ::ssyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, stbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const
{
    return ::stbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, stbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const
{
    return ::stbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, stpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const
{
    return ::stpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, stpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const
{
    return ::stpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, strmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const
{
    return ::strmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, strsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const
{
    return ::strsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, sgem2vu>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11, float v12, const int v13) const
{
    return ::sgem2vu_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
}

void BlasInterface <OpenBlas, cgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const
{
    return ::cgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, cgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const
{
    return ::cgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, cgerc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const
{
    return ::cgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, cgeru>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const
{
    return ::cgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, chbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const
{
    return ::chbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, chemv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const
{
    return ::chemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, cher>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5, const int v6) const
{
    return ::cher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, cher2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const
{
    return ::cher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, chpmv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, std::complex<float> v7, const int v8) const
{
    return ::chpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, chpr>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5) const
{
    return ::chpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, chpr2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7) const
{
    return ::chpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, ctbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const
{
    return ::ctbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, ctbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const
{
    return ::ctbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, ctpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const
{
    return ::ctpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, ctpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const
{
    return ::ctpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, ctrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const
{
    return ::ctrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, ctrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const
{
    return ::ctrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, cgem2vc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11, std::complex<float> v12, const int v13) const
{
    return ::cgem2vc_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
}

void BlasInterface <OpenBlas, scgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const float v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const
{
    return ::scgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, dgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const
{
    return ::dgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, dgemv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const
{
    return ::dgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, dger>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const
{
    return ::dger_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, dsbmv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const
{
    return ::dsbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, dspmv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const double v4, const int v5, const double v6, double v7, const int v8) const
{
    return ::dspmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, dspr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5) const
{
    return ::dspr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, dspr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7) const
{
    return ::dspr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, dsymv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, double v8, const int v9) const
{
    return ::dsymv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, dsyr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5, const int v6) const
{
    return ::dsyr_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, dsyr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const
{
    return ::dsyr2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, dtbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const
{
    return ::dtbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, dtbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const
{
    return ::dtbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, dtpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const
{
    return ::dtpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, dtpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const
{
    return ::dtpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, dtrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const
{
    return ::dtrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, dtrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const
{
    return ::dtrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, dgem2vu>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11, double v12, const int v13) const
{
    return ::dgem2vu_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
}

void BlasInterface <OpenBlas, zgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const
{
    return ::zgbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, zgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const
{
    return ::zgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, zgerc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const
{
    return ::zgerc_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, zgeru>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const
{
    return ::zgeru_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, zhbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const
{
    return ::zhbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, zhemv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const
{
    return ::zhemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, zher>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5, const int v6) const
{
    return ::zher_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, zher2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const
{
    return ::zher2_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, zhpmv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, std::complex<double> v7, const int v8) const
{
    return ::zhpmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, zhpr>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5) const
{
    return ::zhpr_(v0, v1, v2, v3, v4, v5);
}

void BlasInterface <OpenBlas, zhpr2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7) const
{
    return ::zhpr2_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, ztbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const
{
    return ::ztbmv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, ztbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const
{
    return ::ztbsv_(v0, v1, v2, v3, v4, v5, v6, v7, v8);
}

void BlasInterface <OpenBlas, ztpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const
{
    return ::ztpmv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, ztpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const
{
    return ::ztpsv_(v0, v1, v2, v3, v4, v5, v6);
}

void BlasInterface <OpenBlas, ztrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const
{
    return ::ztrmv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, ztrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const
{
    return ::ztrsv_(v0, v1, v2, v3, v4, v5, v6, v7);
}

void BlasInterface <OpenBlas, zgem2vc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11, std::complex<double> v12, const int v13) const
{
    return ::zgem2vc_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13);
}

void BlasInterface <OpenBlas, dzgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const double v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const
{
    return ::dzgemv_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, sgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const
{
    return ::sgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, ssymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const
{
    return ::ssymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, ssyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const
{
    return ::ssyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, ssyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, float v8, const int v9) const
{
    return ::ssyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, strmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const
{
    return ::strmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, strsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const
{
    return ::strsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, cgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const
{
    return ::cgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, scgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const float v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const
{
    return ::scgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, cgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const
{
    return ::cgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, chemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const
{
    return ::chemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, cher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const float v9, std::complex<float> v10, const int v11) const
{
    return ::cher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, cherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const std::complex<float> v5, const int v6, const float v7, std::complex<float> v8, const int v9) const
{
    return ::cherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, csymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const
{
    return ::csymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, csyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const
{
    return ::csyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, csyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const
{
    return ::csyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, ctrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const
{
    return ::ctrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, ctrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const
{
    return ::ctrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, dgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const
{
    return ::dgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, dsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const
{
    return ::dsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, dsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const
{
    return ::dsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, dsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, double v8, const int v9) const
{
    return ::dsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, dtrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const
{
    return ::dtrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, dtrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const
{
    return ::dtrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, zgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const
{
    return ::zgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, dzgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const double v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const
{
    return ::dzgemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, zgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const
{
    return ::zgemm3m_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12);
}

void BlasInterface <OpenBlas, zhemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const
{
    return ::zhemm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, zher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const double v9, std::complex<double> v10, const int v11) const
{
    return ::zher2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, zherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const std::complex<double> v5, const int v6, const double v7, std::complex<double> v8, const int v9) const
{
    return ::zherk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, zsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const
{
    return ::zsymm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, zsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const
{
    return ::zsyr2k_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
}

void BlasInterface <OpenBlas, zsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const
{
    return ::zsyrk_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

void BlasInterface <OpenBlas, ztrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const
{
    return ::ztrmm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

void BlasInterface <OpenBlas, ztrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const
{
    return ::ztrsm_(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
}

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