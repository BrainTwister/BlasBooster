#pragma once

#include "BlasInterface.h"
#include "FunctionTypes.h"
#include <complex>

namespace BlasBooster {

struct OpenBLAS {};

void OpenBLAS_set_num_threads(int nbThreads);

template <>
struct BlasInterface <OpenBLAS, scabs1>
{
    float operator() (const std::complex<float>* v0) const;
};

template <>
struct BlasInterface <OpenBLAS, sasum>
{
    float operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, saxpy>
{
    void operator() (const int* v0, const float* v1, const float* v2, const int* v3, float* v4, const int* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, saxpby>
{
    void operator() (const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, scasum>
{
    float operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, scnrm2>
{
    float operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, scopy>
{
    void operator() (const int* v0, const float* v1, const int* v2, float* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, sdot>
{
    float operator() (const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, sdsdot>
{
    float operator() (const int* v0, const float* v1, const float* v2, const int* v3, const float* v4, const int* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, snrm2>
{
    float operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, srot>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5, const float* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, srotg>
{
    void operator() (float* v0, float* v1, float* v2, float* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, srotm>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4, const float* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, srotmg>
{
    void operator() (float* v0, float* v1, float* v2, const float* v3, float* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, sscal>
{
    void operator() (const int* v0, const float* v1, float* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, sswap>
{
    void operator() (const int* v0, float* v1, const int* v2, float* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, isamax>
{
    int operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, isamin>
{
    int operator() (const int* v0, const float* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, caxpy>
{
    void operator() (const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, std::complex<float>* v4, const int* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, caxpby>
{
    void operator() (const int* v0, const std::complex<float>* v1, const std::complex<float>* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ccopy>
{
    void operator() (const int* v0, const std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, crotg>
{
    void operator() (std::complex<float>* v0, const std::complex<float>* v1, float* v2, std::complex<float>* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, cscal>
{
    void operator() (const int* v0, const std::complex<float>* v1, std::complex<float>* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, csrot>
{
    void operator() (const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4, const float* v5, const float* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, csscal>
{
    void operator() (const int* v0, const float* v1, std::complex<float>* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, cswap>
{
    void operator() (const int* v0, std::complex<float>* v1, const int* v2, std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, icamax>
{
    int operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, icamin>
{
    int operator() (const int* v0, const std::complex<float>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, dcabs1>
{
    double operator() (const std::complex<double>* v0) const;
};

template <>
struct BlasInterface <OpenBLAS, dasum>
{
    double operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, daxpy>
{
    void operator() (const int* v0, const double* v1, const double* v2, const int* v3, double* v4, const int* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, daxpby>
{
    void operator() (const int* v0, const double* v1, const double* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, dcopy>
{
    void operator() (const int* v0, const double* v1, const int* v2, double* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, ddot>
{
    double operator() (const int* v0, const double* v1, const int* v2, const double* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, dsdot>
{
    double operator() (const int* v0, const float* v1, const int* v2, const float* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, dnrm2>
{
    double operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, drot>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5, const double* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, drotg>
{
    void operator() (double* v0, double* v1, double* v2, double* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, drotm>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4, const double* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, drotmg>
{
    void operator() (double* v0, double* v1, double* v2, const double* v3, double* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, dscal>
{
    void operator() (const int* v0, const double* v1, double* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, dswap>
{
    void operator() (const int* v0, double* v1, const int* v2, double* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, dzasum>
{
    double operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, dznrm2>
{
    double operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, idamax>
{
    int operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, idamin>
{
    int operator() (const int* v0, const double* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, zaxpy>
{
    void operator() (const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, std::complex<double>* v4, const int* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, zaxpby>
{
    void operator() (const int* v0, const std::complex<double>* v1, const std::complex<double>* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, zcopy>
{
    void operator() (const int* v0, const std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, zdrot>
{
    void operator() (const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4, const double* v5, const double* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, zdscal>
{
    void operator() (const int* v0, const double* v1, std::complex<double>* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, zrotg>
{
    void operator() (std::complex<double>* v0, const std::complex<double>* v1, double* v2, std::complex<double>* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, zscal>
{
    void operator() (const int* v0, const std::complex<double>* v1, std::complex<double>* v2, const int* v3) const;
};

template <>
struct BlasInterface <OpenBLAS, zswap>
{
    void operator() (const int* v0, std::complex<double>* v1, const int* v2, std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, izamax>
{
    int operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, izamin>
{
    int operator() (const int* v0, const std::complex<double>* v1, const int* v2) const;
};

template <>
struct BlasInterface <OpenBLAS, sgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, sgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, sger>
{
    void operator() (const int* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, ssbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const float* v3, const float* v4, const int* v5, const float* v6, const int* v7, const float* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, sspmv>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const float* v4, const int* v5, const float* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, sspr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, sspr2>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, ssymv>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, ssyr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ssyr2>
{
    void operator() (const char* v0, const int* v1, const float* v2, const float* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, stbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, stbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const float* v5, const int* v6, float* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, stpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, stpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, float* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, strmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, strsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const float* v4, const int* v5, float* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, cgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, cgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, cgerc>
{
    void operator() (const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, cgeru>
{
    void operator() (const int* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, chbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, chemv>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, cher>
{
    void operator() (const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, cher2>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, chpmv>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const std::complex<float>* v4, const int* v5, const std::complex<float>* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, chpr>
{
    void operator() (const char* v0, const int* v1, const float* v2, const std::complex<float>* v3, const int* v4, std::complex<float>* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, chpr2>
{
    void operator() (const char* v0, const int* v1, const std::complex<float>* v2, const std::complex<float>* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, ctbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, ctbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<float>* v5, const int* v6, std::complex<float>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, ctpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ctpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, std::complex<float>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ctrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, ctrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<float>* v4, const int* v5, std::complex<float>* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, dgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, dgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, dger>
{
    void operator() (const int* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, dsbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const double* v3, const double* v4, const int* v5, const double* v6, const int* v7, const double* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, dspmv>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const double* v4, const int* v5, const double* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, dspr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, dspr2>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, dsymv>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, dsyr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, dsyr2>
{
    void operator() (const char* v0, const int* v1, const double* v2, const double* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, dtbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, dtbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const double* v5, const int* v6, double* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, dtpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, dtpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, double* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, dtrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, dtrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const double* v4, const int* v5, double* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, zgbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, zgemv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, zgerc>
{
    void operator() (const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, zgeru>
{
    void operator() (const int* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, zhbmv>
{
    void operator() (const char* v0, const int* v1, const int* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, zhemv>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, zher>
{
    void operator() (const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, zher2>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, zhpmv>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const std::complex<double>* v4, const int* v5, const std::complex<double>* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, zhpr>
{
    void operator() (const char* v0, const int* v1, const double* v2, const std::complex<double>* v3, const int* v4, std::complex<double>* v5) const;
};

template <>
struct BlasInterface <OpenBLAS, zhpr2>
{
    void operator() (const char* v0, const int* v1, const std::complex<double>* v2, const std::complex<double>* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, ztbmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, ztbsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const int* v4, const std::complex<double>* v5, const int* v6, std::complex<double>* v7, const int* v8) const;
};

template <>
struct BlasInterface <OpenBLAS, ztpmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ztpsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, std::complex<double>* v5, const int* v6) const;
};

template <>
struct BlasInterface <OpenBLAS, ztrmv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, ztrsv>
{
    void operator() (const char* v0, const char* v1, const char* v2, const int* v3, const std::complex<double>* v4, const int* v5, std::complex<double>* v6, const int* v7) const;
};

template <>
struct BlasInterface <OpenBLAS, sgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const float* v5, const float* v6, const int* v7, const float* v8, const int* v9, const float* v10, float* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, ssymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, ssyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, const int* v8, const float* v9, float* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, ssyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const float* v5, const int* v6, const float* v7, float* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, strmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, strsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const float* v6, const float* v7, const int* v8, float* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, cgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, cgemm3m>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<float>* v5, const std::complex<float>* v6, const int* v7, const std::complex<float>* v8, const int* v9, const std::complex<float>* v10, std::complex<float>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, chemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, cher2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const float* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, cherk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const float* v4, const std::complex<float>* v5, const int* v6, const float* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, csymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, csyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, const int* v8, const std::complex<float>* v9, std::complex<float>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, csyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<float>* v4, const std::complex<float>* v5, const int* v6, const std::complex<float>* v7, std::complex<float>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, ctrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, ctrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<float>* v6, const std::complex<float>* v7, const int* v8, std::complex<float>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, dgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const double* v5, const double* v6, const int* v7, const double* v8, const int* v9, const double* v10, double* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, dsymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, dsyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, const int* v8, const double* v9, double* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, dsyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const double* v5, const int* v6, const double* v7, double* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, dtrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, dtrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const double* v6, const double* v7, const int* v8, double* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, zgemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, zgemm3m>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const int* v4, const std::complex<double>* v5, const std::complex<double>* v6, const int* v7, const std::complex<double>* v8, const int* v9, const std::complex<double>* v10, std::complex<double>* v11, const int* v12) const;
};

template <>
struct BlasInterface <OpenBLAS, zhemm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, zher2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const double* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, zherk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const double* v4, const std::complex<double>* v5, const int* v6, const double* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, zsymm>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, zsyr2k>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, const int* v8, const std::complex<double>* v9, std::complex<double>* v10, const int* v11) const;
};

template <>
struct BlasInterface <OpenBLAS, zsyrk>
{
    void operator() (const char* v0, const char* v1, const int* v2, const int* v3, const std::complex<double>* v4, const std::complex<double>* v5, const int* v6, const std::complex<double>* v7, std::complex<double>* v8, const int* v9) const;
};

template <>
struct BlasInterface <OpenBLAS, ztrmm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, ztrsm>
{
    void operator() (const char* v0, const char* v1, const char* v2, const char* v3, const int* v4, const int* v5, const std::complex<double>* v6, const std::complex<double>* v7, const int* v8, std::complex<double>* v9, const int* v10) const;
};

template <>
struct BlasInterface <OpenBLAS, cdotc>
{
    std::complex<float> operator() (const int* v0, const std::complex<float>* v1, const int* v2, const std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, cdotu>
{
    std::complex<float> operator() (const int* v0, const std::complex<float>* v1, const int* v2, const std::complex<float>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, zdotc>
{
    std::complex<double> operator() (const int* v0, const std::complex<double>* v1, const int* v2, const std::complex<double>* v3, const int* v4) const;
};

template <>
struct BlasInterface <OpenBLAS, zdotu>
{
    std::complex<double> operator() (const int* v0, const std::complex<double>* v1, const int* v2, const std::complex<double>* v3, const int* v4) const;
};

} // namespace BlasBooster
