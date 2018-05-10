#pragma once

#include "BlasInterface.h"
#include <string>

namespace BlasBooster {

struct IntelMKL {};

void mkl_set_num_threads(int nbThreads);

float BlasInterface <IntelMKL, scabs1>::operator() (
    const std::complex<float> v0) const;

float BlasInterface <IntelMKL, sasum>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <IntelMKL, saxpy>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4, const int v5) const;

void BlasInterface <IntelMKL, saxpby>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <IntelMKL, saxpyi>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4) const;

float BlasInterface <IntelMKL, scasum>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

float BlasInterface <IntelMKL, scnrm2>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

void BlasInterface <IntelMKL, scopy>::operator() (
    const int v0, const float v1, const int v2, float v3, const int v4) const;

float BlasInterface <IntelMKL, sdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const;

float BlasInterface <IntelMKL, sdoti>::operator() (
    const int v0, const float v1, const int v2, const float v3) const;

float BlasInterface <IntelMKL, sdsdot>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, const int v5) const;

void BlasInterface <IntelMKL, sgthr>::operator() (
    const int v0, const float v1, float v2, const int v3) const;

void BlasInterface <IntelMKL, sgthrz>::operator() (
    const int v0, float v1, float v2, const int v3) const;

float BlasInterface <IntelMKL, snrm2>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <IntelMKL, srot>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5, const float v6) const;

void BlasInterface <IntelMKL, srotg>::operator() (
    float v0, float v1, float v2, float v3) const;

void BlasInterface <IntelMKL, sroti>::operator() (
    const int v0, float v1, const int v2, float v3, const float v4, const float v5) const;

void BlasInterface <IntelMKL, srotm>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5) const;

void BlasInterface <IntelMKL, srotmg>::operator() (
    float v0, float v1, float v2, const float v3, float v4) const;

void BlasInterface <IntelMKL, sscal>::operator() (
    const int v0, const float v1, float v2, const int v3) const;

void BlasInterface <IntelMKL, ssctr>::operator() (
    const int v0, const float v1, const int v2, float v3) const;

void BlasInterface <IntelMKL, sswap>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4) const;

int BlasInterface <IntelMKL, isamax>::operator() (
    const int v0, const float v1, const int v2) const;

int BlasInterface <IntelMKL, isamin>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <IntelMKL, caxpy>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4, const int v5) const;

void BlasInterface <IntelMKL, caxpby>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <IntelMKL, caxpyi>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4) const;

void BlasInterface <IntelMKL, ccopy>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const;

void BlasInterface <IntelMKL, cgthr>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <IntelMKL, cgthrz>::operator() (
    const int v0, std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <IntelMKL, crotg>::operator() (
    std::complex<float> v0, const std::complex<float> v1, float v2, std::complex<float> v3) const;

void BlasInterface <IntelMKL, cscal>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <IntelMKL, csctr>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3) const;

void BlasInterface <IntelMKL, csrot>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4, const float v5, const float v6) const;

void BlasInterface <IntelMKL, csscal>::operator() (
    const int v0, const float v1, std::complex<float> v2, const int v3) const;

void BlasInterface <IntelMKL, cswap>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const;

int BlasInterface <IntelMKL, icamax>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

int BlasInterface <IntelMKL, icamin>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

double BlasInterface <IntelMKL, dcabs1>::operator() (
    const std::complex<double> v0) const;

double BlasInterface <IntelMKL, dasum>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <IntelMKL, daxpy>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4, const int v5) const;

void BlasInterface <IntelMKL, daxpby>::operator() (
    const int v0, const double v1, const double v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <IntelMKL, daxpyi>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4) const;

void BlasInterface <IntelMKL, dcopy>::operator() (
    const int v0, const double v1, const int v2, double v3, const int v4) const;

double BlasInterface <IntelMKL, ddot>::operator() (
    const int v0, const double v1, const int v2, const double v3, const int v4) const;

double BlasInterface <IntelMKL, dsdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const;

double BlasInterface <IntelMKL, ddoti>::operator() (
    const int v0, const double v1, const int v2, const double v3) const;

void BlasInterface <IntelMKL, dgthr>::operator() (
    const int v0, const double v1, double v2, const int v3) const;

void BlasInterface <IntelMKL, dgthrz>::operator() (
    const int v0, double v1, double v2, const int v3) const;

double BlasInterface <IntelMKL, dnrm2>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <IntelMKL, drot>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5, const double v6) const;

void BlasInterface <IntelMKL, drotg>::operator() (
    double v0, double v1, double v2, double v3) const;

void BlasInterface <IntelMKL, droti>::operator() (
    const int v0, double v1, const int v2, double v3, const double v4, const double v5) const;

void BlasInterface <IntelMKL, drotm>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5) const;

void BlasInterface <IntelMKL, drotmg>::operator() (
    double v0, double v1, double v2, const double v3, double v4) const;

void BlasInterface <IntelMKL, dscal>::operator() (
    const int v0, const double v1, double v2, const int v3) const;

void BlasInterface <IntelMKL, dsctr>::operator() (
    const int v0, const double v1, const int v2, double v3) const;

void BlasInterface <IntelMKL, dswap>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4) const;

double BlasInterface <IntelMKL, dzasum>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

double BlasInterface <IntelMKL, dznrm2>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

int BlasInterface <IntelMKL, idamax>::operator() (
    const int v0, const double v1, const int v2) const;

int BlasInterface <IntelMKL, idamin>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <IntelMKL, zaxpy>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4, const int v5) const;

void BlasInterface <IntelMKL, zaxpby>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <IntelMKL, zaxpyi>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4) const;

void BlasInterface <IntelMKL, zcopy>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const;

void BlasInterface <IntelMKL, zdrot>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4, const double v5, const double v6) const;

void BlasInterface <IntelMKL, zdscal>::operator() (
    const int v0, const double v1, std::complex<double> v2, const int v3) const;

void BlasInterface <IntelMKL, zgthr>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <IntelMKL, zgthrz>::operator() (
    const int v0, std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <IntelMKL, zrotg>::operator() (
    std::complex<double> v0, const std::complex<double> v1, double v2, std::complex<double> v3) const;

void BlasInterface <IntelMKL, zscal>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <IntelMKL, zsctr>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3) const;

void BlasInterface <IntelMKL, zswap>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const;

int BlasInterface <IntelMKL, izamax>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

int BlasInterface <IntelMKL, izamin>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

void BlasInterface <IntelMKL, sgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const;

void BlasInterface <IntelMKL, sgemv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const;

void BlasInterface <IntelMKL, sger>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <IntelMKL, ssbmv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const;

void BlasInterface <IntelMKL, sspmv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const float v4, const int v5, const float v6, float v7, const int v8) const;

void BlasInterface <IntelMKL, sspr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5) const;

void BlasInterface <IntelMKL, sspr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7) const;

void BlasInterface <IntelMKL, ssymv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, float v8, const int v9) const;

void BlasInterface <IntelMKL, ssyr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5, const int v6) const;

void BlasInterface <IntelMKL, ssyr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <IntelMKL, stbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <IntelMKL, stbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <IntelMKL, stpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <IntelMKL, stpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <IntelMKL, strmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const;

void BlasInterface <IntelMKL, strsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const;

void BlasInterface <IntelMKL, sgem2vu>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11, float v12, const int v13) const;

void BlasInterface <IntelMKL, cgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <IntelMKL, cgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <IntelMKL, cgerc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, cgeru>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, chbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <IntelMKL, chemv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const;

void BlasInterface <IntelMKL, cher>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5, const int v6) const;

void BlasInterface <IntelMKL, cher2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, chpmv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, chpr>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5) const;

void BlasInterface <IntelMKL, chpr2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7) const;

void BlasInterface <IntelMKL, ctbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, ctbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <IntelMKL, ctpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <IntelMKL, ctpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <IntelMKL, ctrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const;

void BlasInterface <IntelMKL, ctrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const;

void BlasInterface <IntelMKL, cgem2vc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11, std::complex<float> v12, const int v13) const;

void BlasInterface <IntelMKL, scgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const float v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <IntelMKL, dgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const;

void BlasInterface <IntelMKL, dgemv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const;

void BlasInterface <IntelMKL, dger>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <IntelMKL, dsbmv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const;

void BlasInterface <IntelMKL, dspmv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const double v4, const int v5, const double v6, double v7, const int v8) const;

void BlasInterface <IntelMKL, dspr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5) const;

void BlasInterface <IntelMKL, dspr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7) const;

void BlasInterface <IntelMKL, dsymv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, double v8, const int v9) const;

void BlasInterface <IntelMKL, dsyr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5, const int v6) const;

void BlasInterface <IntelMKL, dsyr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <IntelMKL, dtbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <IntelMKL, dtbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <IntelMKL, dtpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <IntelMKL, dtpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <IntelMKL, dtrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const;

void BlasInterface <IntelMKL, dtrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const;

void BlasInterface <IntelMKL, dgem2vu>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11, double v12, const int v13) const;

void BlasInterface <IntelMKL, zgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <IntelMKL, zgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <IntelMKL, zgerc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, zgeru>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, zhbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <IntelMKL, zhemv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const;

void BlasInterface <IntelMKL, zher>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5, const int v6) const;

void BlasInterface <IntelMKL, zher2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, zhpmv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, zhpr>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5) const;

void BlasInterface <IntelMKL, zhpr2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7) const;

void BlasInterface <IntelMKL, ztbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, ztbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <IntelMKL, ztpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <IntelMKL, ztpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <IntelMKL, ztrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const;

void BlasInterface <IntelMKL, ztrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const;

void BlasInterface <IntelMKL, zgem2vc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11, std::complex<double> v12, const int v13) const;

void BlasInterface <IntelMKL, dzgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const double v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <IntelMKL, sgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const;

void BlasInterface <IntelMKL, ssymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const;

void BlasInterface <IntelMKL, ssyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const;

void BlasInterface <IntelMKL, ssyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, float v8, const int v9) const;

void BlasInterface <IntelMKL, strmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const;

void BlasInterface <IntelMKL, strsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const;

void BlasInterface <IntelMKL, cgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <IntelMKL, scgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const float v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <IntelMKL, cgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <IntelMKL, chemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <IntelMKL, cher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const float v9, std::complex<float> v10, const int v11) const;

void BlasInterface <IntelMKL, cherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const std::complex<float> v5, const int v6, const float v7, std::complex<float> v8, const int v9) const;

void BlasInterface <IntelMKL, csymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <IntelMKL, csyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <IntelMKL, csyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const;

void BlasInterface <IntelMKL, ctrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const;

void BlasInterface <IntelMKL, ctrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const;

void BlasInterface <IntelMKL, dgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const;

void BlasInterface <IntelMKL, dsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const;

void BlasInterface <IntelMKL, dsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const;

void BlasInterface <IntelMKL, dsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, double v8, const int v9) const;

void BlasInterface <IntelMKL, dtrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const;

void BlasInterface <IntelMKL, dtrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const;

void BlasInterface <IntelMKL, zgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <IntelMKL, dzgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const double v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <IntelMKL, zgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <IntelMKL, zhemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <IntelMKL, zher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const double v9, std::complex<double> v10, const int v11) const;

void BlasInterface <IntelMKL, zherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const std::complex<double> v5, const int v6, const double v7, std::complex<double> v8, const int v9) const;

void BlasInterface <IntelMKL, zsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <IntelMKL, zsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <IntelMKL, zsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const;

void BlasInterface <IntelMKL, ztrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const;

void BlasInterface <IntelMKL, ztrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const;

std::complex<float> BlasInterface <IntelMKL, cdotc>::operator() (
    const int v0, const std::complex<float> v1, const int v2, const std::complex<float> v3, const int v4) const;

std::complex<float> BlasInterface <IntelMKL, cdotu>::operator() (
    const int v0, const std::complex<float> v1, const int v2, const std::complex<float> v3, const int v4) const;

std::complex<double> BlasInterface <IntelMKL, zdotc>::operator() (
    const int v0, const std::complex<double> v1, const int v2, const std::complex<double> v3, const int v4) const;

std::complex<double> BlasInterface <IntelMKL, zdotu>::operator() (
    const int v0, const std::complex<double> v1, const int v2, const std::complex<double> v3, const int v4) const;

void BlasInterface <IntelMKL, dcsrmm>::operator() (
    const char v0, const int v1, const int v2, const int v3, const double v4, const char v5, const double v6, const int v7, const int v8, const int v9, const double v10, const int v11, const double v12, double v13, const int v14) const;

void BlasInterface <IntelMKL, dcsrmultcsr>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const int v5, double v6, int v7, int v8, double v9, int v10, int v11, double v12, int v13, int v14, const int v15, int v16) const;

} // namespace BlasBooster