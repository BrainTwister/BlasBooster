#pragma once

#include "BlasInterface.h"
#include "FunctionTypes.h"

namespace BlasBooster {

struct IntelMKL {};

void mkl_set_num_threads(int nbThreads);

template <>
struct BlasInterface <IntelMKL, scabs1>
{
    float operator() (const std::complex<float>* v0) const;
};

template <>
struct BlasInterface <IntelMKL, sasum>
{
    float operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, saxpy>
{
    void operator() (const int* v0, const float* v1, const float* v2, const int* v3, float* v4, const int* v5) const;
};

template <>
struct BlasInterface <IntelMKL, saxpby>
{
    void operator() (const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, scasum>
{
    float operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, scnrm2>
{
    float operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, scopy>
{
    void operator() (const int* v0, const float* v1, const int* v2, float* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, sdot>
{
    float operator() (const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, sdsdot>
{
    float operator() (const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, const int* v5) const;
};

template <>
struct BlasInterface <IntelMKL, snrm2>
{
    float operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, srot>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5, const float* v6) const;
};

template <>
struct BlasInterface <IntelMKL, srotg>
{
    void operator() (float* v0, float* v1, float* v2, float* v3) const;
};

template <>
struct BlasInterface <IntelMKL, srotm>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5) const;
};

template <>
struct BlasInterface <IntelMKL, srotmg>
{
    void operator() (float* v0, float* v1, float* v2, const float* v3, float* v4) const;
};

template <>
struct BlasInterface <IntelMKL, sscal>
{
    void operator() (const int* v0, const float* v1, float* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, sswap>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, isamax>
{
    int operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, isamin>
{
    int operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, caxpy>
{
    void operator() (const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, std::complex<float>* v4, const int* v5) const;
};

template <>
struct BlasInterface <IntelMKL, caxpby>
{
    void operator() (const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ccopy>
{
    void operator() (const int* v0, const std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, crotg>
{
    void operator() (std::complex<float>* v0, const std::complex<float>* v1, float* v2, std::complex<float>* v3) const;
};

template <>
struct BlasInterface <IntelMKL, cscal>
{
    void operator() (const int* v0, const std::complex<float>* v1, std::complex<float>* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, csrot>
{
    void operator() (const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4, const float* v5, const float* v6) const;
};

template <>
struct BlasInterface <IntelMKL, csscal>
{
    void operator() (const int* v0, const float* v1, std::complex<float>* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, cswap>
{
    void operator() (const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, icamax>
{
    int operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, icamin>
{
    int operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, dcabs1>
{
    double operator() (const std::complex<double>* v0) const;
};

template <>
struct BlasInterface <IntelMKL, dasum>
{
    double operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, daxpy>
{
    void operator() (const int* v0, const double* v1, const double* v2, const int* v3, double* v4, const int* v5) const;
};

template <>
struct BlasInterface <IntelMKL, daxpby>
{
    void operator() (const int* v0, const double* v1, const double* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, dcopy>
{
    void operator() (const int* v0, const double* v1, const int* v2, double* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, ddot>
{
    double operator() (const int* v0, const double* v1, const int* v2, const double* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, dsdot>
{
    double operator() (const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, dnrm2>
{
    double operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, drot>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5, const double* v6) const;
};

template <>
struct BlasInterface <IntelMKL, drotg>
{
    void operator() (double* v0, double* v1, double* v2, double* v3) const;
};

template <>
struct BlasInterface <IntelMKL, drotm>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5) const;
};

template <>
struct BlasInterface <IntelMKL, drotmg>
{
    void operator() (double* v0, double* v1, double* v2, const double* v3, double* v4) const;
};

template <>
struct BlasInterface <IntelMKL, dscal>
{
    void operator() (const int* v0, const double* v1, double* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, dswap>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, dzasum>
{
    double operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, dznrm2>
{
    double operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, idamax>
{
    int operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, idamin>
{
    int operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, zaxpy>
{
    void operator() (const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, std::complex<double>* v4, const int* v5) const;
};

template <>
struct BlasInterface <IntelMKL, zaxpby>
{
    void operator() (const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, zcopy>
{
    void operator() (const int* v0, const std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, zdrot>
{
    void operator() (const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4, const double* v5, const double* v6) const;
};

template <>
struct BlasInterface <IntelMKL, zdscal>
{
    void operator() (const int* v0, const double* v1, std::complex<double>* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, zrotg>
{
    void operator() (std::complex<double>* v0, const std::complex<double>* v1, double* v2, std::complex<double>* v3) const;
};

template <>
struct BlasInterface <IntelMKL, zscal>
{
    void operator() (const int* v0, const std::complex<double>* v1, std::complex<double>* v2, const int* v3) const;
};

template <>
struct BlasInterface <IntelMKL, zswap>
{
    void operator() (const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, izamax>
{
    int operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, izamin>
{
    int operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <IntelMKL, sgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, sgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, sger>
{
    void operator() (const int* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, ssbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, sspmv>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const float* v4, const int* v5, const float* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, sspr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5) const;
};

template <>
struct BlasInterface <IntelMKL, sspr2>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7) const;
};

template <>
struct BlasInterface <IntelMKL, ssymv>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, ssyr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ssyr2>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, stbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, stbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, stpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, stpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, strmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, strsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, cgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, cgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, cgerc>
{
    void operator() (const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, cgeru>
{
    void operator() (const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, chbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, chemv>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, cher>
{
    void operator() (const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, cher2>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, chpmv>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, chpr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5) const;
};

template <>
struct BlasInterface <IntelMKL, chpr2>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7) const;
};

template <>
struct BlasInterface <IntelMKL, ctbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, ctbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, ctpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ctpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ctrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, ctrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, dgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, dgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, dger>
{
    void operator() (const int* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, dsbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, dspmv>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const double* v4, const int* v5, const double* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, dspr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5) const;
};

template <>
struct BlasInterface <IntelMKL, dspr2>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7) const;
};

template <>
struct BlasInterface <IntelMKL, dsymv>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, dsyr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, dsyr2>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, dtbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, dtbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, dtpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, dtpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, dtrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, dtrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, zgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, zgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, zgerc>
{
    void operator() (const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, zgeru>
{
    void operator() (const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, zhbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, zhemv>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, zher>
{
    void operator() (const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, zher2>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, zhpmv>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, zhpr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5) const;
};

template <>
struct BlasInterface <IntelMKL, zhpr2>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7) const;
};

template <>
struct BlasInterface <IntelMKL, ztbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, ztbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <IntelMKL, ztpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ztpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <IntelMKL, ztrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, ztrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const;
};

template <>
struct BlasInterface <IntelMKL, sgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, ssymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, ssyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, ssyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, strmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, strsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, cgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, cgemm3m>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, chemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, cher2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const float* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, cherk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const std::complex<float>* v5, const int* v6, const float* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, csymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, csyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, csyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, ctrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, ctrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, dgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, dsymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, dsyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, dsyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, dtrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, dtrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, zgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, zgemm3m>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <IntelMKL, zhemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, zher2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const double* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, zherk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const std::complex<double>* v5, const int* v6, const double* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, zsymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, zsyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <IntelMKL, zsyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <IntelMKL, ztrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, ztrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <IntelMKL, cdotc>
{
    std::complex<float> operator() (const int* v0, const std::complex<float>* v1, const int* v2, const std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, cdotu>
{
    std::complex<float> operator() (const int* v0, const std::complex<float>* v1, const int* v2, const std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, zdotc>
{
    std::complex<double> operator() (const int* v0, const std::complex<double>* v1, const int* v2, const std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, zdotu>
{
    std::complex<double> operator() (const int* v0, const std::complex<double>* v1, const int* v2, const std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <IntelMKL, dcsrmm>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const double* v4, const char* v5, const double* v6, const int* v7, const int* v8, const int* v9, const double* v10, const int* v11, const double* v12, double* v13, const int* v14) const;
};

template <>
struct BlasInterface <IntelMKL, dcsrmultcsr>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const int* v5, double* v6, int* v7, int* v8, double* v9, int* v10, int* v11, double* v12, int* v13, int* v14, const int* v15, int* v16) const;
};

} // namespace BlasBooster