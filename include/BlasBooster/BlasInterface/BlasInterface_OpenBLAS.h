#pragma once

#include "BlasInterface.h"
#include <string>

namespace BlasBooster {

struct OpenBLAS {};

struct scabs1
{
    static std::string name() { return "scabs1"; }
};

struct sasum
{
    static std::string name() { return "sasum"; }
};

struct saxpy
{
    static std::string name() { return "saxpy"; }
};

struct saxpby
{
    static std::string name() { return "saxpby"; }
};

struct saxpyi
{
    static std::string name() { return "saxpyi"; }
};

struct scasum
{
    static std::string name() { return "scasum"; }
};

struct scnrm2
{
    static std::string name() { return "scnrm2"; }
};

struct scopy
{
    static std::string name() { return "scopy"; }
};

struct sdot
{
    static std::string name() { return "sdot"; }
};

struct sdoti
{
    static std::string name() { return "sdoti"; }
};

struct sdsdot
{
    static std::string name() { return "sdsdot"; }
};

struct sgthr
{
    static std::string name() { return "sgthr"; }
};

struct sgthrz
{
    static std::string name() { return "sgthrz"; }
};

struct snrm2
{
    static std::string name() { return "snrm2"; }
};

struct srot
{
    static std::string name() { return "srot"; }
};

struct srotg
{
    static std::string name() { return "srotg"; }
};

struct sroti
{
    static std::string name() { return "sroti"; }
};

struct srotm
{
    static std::string name() { return "srotm"; }
};

struct srotmg
{
    static std::string name() { return "srotmg"; }
};

struct sscal
{
    static std::string name() { return "sscal"; }
};

struct ssctr
{
    static std::string name() { return "ssctr"; }
};

struct sswap
{
    static std::string name() { return "sswap"; }
};

struct isamax
{
    static std::string name() { return "isamax"; }
};

struct isamin
{
    static std::string name() { return "isamin"; }
};

struct caxpy
{
    static std::string name() { return "caxpy"; }
};

struct caxpby
{
    static std::string name() { return "caxpby"; }
};

struct caxpyi
{
    static std::string name() { return "caxpyi"; }
};

struct ccopy
{
    static std::string name() { return "ccopy"; }
};

struct cgthr
{
    static std::string name() { return "cgthr"; }
};

struct cgthrz
{
    static std::string name() { return "cgthrz"; }
};

struct crotg
{
    static std::string name() { return "crotg"; }
};

struct cscal
{
    static std::string name() { return "cscal"; }
};

struct csctr
{
    static std::string name() { return "csctr"; }
};

struct csrot
{
    static std::string name() { return "csrot"; }
};

struct csscal
{
    static std::string name() { return "csscal"; }
};

struct cswap
{
    static std::string name() { return "cswap"; }
};

struct icamax
{
    static std::string name() { return "icamax"; }
};

struct icamin
{
    static std::string name() { return "icamin"; }
};

struct dcabs1
{
    static std::string name() { return "dcabs1"; }
};

struct dasum
{
    static std::string name() { return "dasum"; }
};

struct daxpy
{
    static std::string name() { return "daxpy"; }
};

struct daxpby
{
    static std::string name() { return "daxpby"; }
};

struct daxpyi
{
    static std::string name() { return "daxpyi"; }
};

struct dcopy
{
    static std::string name() { return "dcopy"; }
};

struct ddot
{
    static std::string name() { return "ddot"; }
};

struct dsdot
{
    static std::string name() { return "dsdot"; }
};

struct ddoti
{
    static std::string name() { return "ddoti"; }
};

struct dgthr
{
    static std::string name() { return "dgthr"; }
};

struct dgthrz
{
    static std::string name() { return "dgthrz"; }
};

struct dnrm2
{
    static std::string name() { return "dnrm2"; }
};

struct drot
{
    static std::string name() { return "drot"; }
};

struct drotg
{
    static std::string name() { return "drotg"; }
};

struct droti
{
    static std::string name() { return "droti"; }
};

struct drotm
{
    static std::string name() { return "drotm"; }
};

struct drotmg
{
    static std::string name() { return "drotmg"; }
};

struct dscal
{
    static std::string name() { return "dscal"; }
};

struct dsctr
{
    static std::string name() { return "dsctr"; }
};

struct dswap
{
    static std::string name() { return "dswap"; }
};

struct dzasum
{
    static std::string name() { return "dzasum"; }
};

struct dznrm2
{
    static std::string name() { return "dznrm2"; }
};

struct idamax
{
    static std::string name() { return "idamax"; }
};

struct idamin
{
    static std::string name() { return "idamin"; }
};

struct zaxpy
{
    static std::string name() { return "zaxpy"; }
};

struct zaxpby
{
    static std::string name() { return "zaxpby"; }
};

struct zaxpyi
{
    static std::string name() { return "zaxpyi"; }
};

struct zcopy
{
    static std::string name() { return "zcopy"; }
};

struct zdrot
{
    static std::string name() { return "zdrot"; }
};

struct zdscal
{
    static std::string name() { return "zdscal"; }
};

struct zgthr
{
    static std::string name() { return "zgthr"; }
};

struct zgthrz
{
    static std::string name() { return "zgthrz"; }
};

struct zrotg
{
    static std::string name() { return "zrotg"; }
};

struct zscal
{
    static std::string name() { return "zscal"; }
};

struct zsctr
{
    static std::string name() { return "zsctr"; }
};

struct zswap
{
    static std::string name() { return "zswap"; }
};

struct izamax
{
    static std::string name() { return "izamax"; }
};

struct izamin
{
    static std::string name() { return "izamin"; }
};

struct sgbmv
{
    static std::string name() { return "sgbmv"; }
};

struct sgemv
{
    static std::string name() { return "sgemv"; }
};

struct sger
{
    static std::string name() { return "sger"; }
};

struct ssbmv
{
    static std::string name() { return "ssbmv"; }
};

struct sspmv
{
    static std::string name() { return "sspmv"; }
};

struct sspr
{
    static std::string name() { return "sspr"; }
};

struct sspr2
{
    static std::string name() { return "sspr2"; }
};

struct ssymv
{
    static std::string name() { return "ssymv"; }
};

struct ssyr
{
    static std::string name() { return "ssyr"; }
};

struct ssyr2
{
    static std::string name() { return "ssyr2"; }
};

struct stbmv
{
    static std::string name() { return "stbmv"; }
};

struct stbsv
{
    static std::string name() { return "stbsv"; }
};

struct stpmv
{
    static std::string name() { return "stpmv"; }
};

struct stpsv
{
    static std::string name() { return "stpsv"; }
};

struct strmv
{
    static std::string name() { return "strmv"; }
};

struct strsv
{
    static std::string name() { return "strsv"; }
};

struct sgem2vu
{
    static std::string name() { return "sgem2vu"; }
};

struct cgbmv
{
    static std::string name() { return "cgbmv"; }
};

struct cgemv
{
    static std::string name() { return "cgemv"; }
};

struct cgerc
{
    static std::string name() { return "cgerc"; }
};

struct cgeru
{
    static std::string name() { return "cgeru"; }
};

struct chbmv
{
    static std::string name() { return "chbmv"; }
};

struct chemv
{
    static std::string name() { return "chemv"; }
};

struct cher
{
    static std::string name() { return "cher"; }
};

struct cher2
{
    static std::string name() { return "cher2"; }
};

struct chpmv
{
    static std::string name() { return "chpmv"; }
};

struct chpr
{
    static std::string name() { return "chpr"; }
};

struct chpr2
{
    static std::string name() { return "chpr2"; }
};

struct ctbmv
{
    static std::string name() { return "ctbmv"; }
};

struct ctbsv
{
    static std::string name() { return "ctbsv"; }
};

struct ctpmv
{
    static std::string name() { return "ctpmv"; }
};

struct ctpsv
{
    static std::string name() { return "ctpsv"; }
};

struct ctrmv
{
    static std::string name() { return "ctrmv"; }
};

struct ctrsv
{
    static std::string name() { return "ctrsv"; }
};

struct cgem2vc
{
    static std::string name() { return "cgem2vc"; }
};

struct scgemv
{
    static std::string name() { return "scgemv"; }
};

struct dgbmv
{
    static std::string name() { return "dgbmv"; }
};

struct dgemv
{
    static std::string name() { return "dgemv"; }
};

struct dger
{
    static std::string name() { return "dger"; }
};

struct dsbmv
{
    static std::string name() { return "dsbmv"; }
};

struct dspmv
{
    static std::string name() { return "dspmv"; }
};

struct dspr
{
    static std::string name() { return "dspr"; }
};

struct dspr2
{
    static std::string name() { return "dspr2"; }
};

struct dsymv
{
    static std::string name() { return "dsymv"; }
};

struct dsyr
{
    static std::string name() { return "dsyr"; }
};

struct dsyr2
{
    static std::string name() { return "dsyr2"; }
};

struct dtbmv
{
    static std::string name() { return "dtbmv"; }
};

struct dtbsv
{
    static std::string name() { return "dtbsv"; }
};

struct dtpmv
{
    static std::string name() { return "dtpmv"; }
};

struct dtpsv
{
    static std::string name() { return "dtpsv"; }
};

struct dtrmv
{
    static std::string name() { return "dtrmv"; }
};

struct dtrsv
{
    static std::string name() { return "dtrsv"; }
};

struct dgem2vu
{
    static std::string name() { return "dgem2vu"; }
};

struct zgbmv
{
    static std::string name() { return "zgbmv"; }
};

struct zgemv
{
    static std::string name() { return "zgemv"; }
};

struct zgerc
{
    static std::string name() { return "zgerc"; }
};

struct zgeru
{
    static std::string name() { return "zgeru"; }
};

struct zhbmv
{
    static std::string name() { return "zhbmv"; }
};

struct zhemv
{
    static std::string name() { return "zhemv"; }
};

struct zher
{
    static std::string name() { return "zher"; }
};

struct zher2
{
    static std::string name() { return "zher2"; }
};

struct zhpmv
{
    static std::string name() { return "zhpmv"; }
};

struct zhpr
{
    static std::string name() { return "zhpr"; }
};

struct zhpr2
{
    static std::string name() { return "zhpr2"; }
};

struct ztbmv
{
    static std::string name() { return "ztbmv"; }
};

struct ztbsv
{
    static std::string name() { return "ztbsv"; }
};

struct ztpmv
{
    static std::string name() { return "ztpmv"; }
};

struct ztpsv
{
    static std::string name() { return "ztpsv"; }
};

struct ztrmv
{
    static std::string name() { return "ztrmv"; }
};

struct ztrsv
{
    static std::string name() { return "ztrsv"; }
};

struct zgem2vc
{
    static std::string name() { return "zgem2vc"; }
};

struct dzgemv
{
    static std::string name() { return "dzgemv"; }
};

struct sgemm
{
    static std::string name() { return "sgemm"; }
};

struct ssymm
{
    static std::string name() { return "ssymm"; }
};

struct ssyr2k
{
    static std::string name() { return "ssyr2k"; }
};

struct ssyrk
{
    static std::string name() { return "ssyrk"; }
};

struct strmm
{
    static std::string name() { return "strmm"; }
};

struct strsm
{
    static std::string name() { return "strsm"; }
};

struct cgemm
{
    static std::string name() { return "cgemm"; }
};

struct scgemm
{
    static std::string name() { return "scgemm"; }
};

struct cgemm3m
{
    static std::string name() { return "cgemm3m"; }
};

struct chemm
{
    static std::string name() { return "chemm"; }
};

struct cher2k
{
    static std::string name() { return "cher2k"; }
};

struct cherk
{
    static std::string name() { return "cherk"; }
};

struct csymm
{
    static std::string name() { return "csymm"; }
};

struct csyr2k
{
    static std::string name() { return "csyr2k"; }
};

struct csyrk
{
    static std::string name() { return "csyrk"; }
};

struct ctrmm
{
    static std::string name() { return "ctrmm"; }
};

struct ctrsm
{
    static std::string name() { return "ctrsm"; }
};

struct dgemm
{
    static std::string name() { return "dgemm"; }
};

struct dsymm
{
    static std::string name() { return "dsymm"; }
};

struct dsyr2k
{
    static std::string name() { return "dsyr2k"; }
};

struct dsyrk
{
    static std::string name() { return "dsyrk"; }
};

struct dtrmm
{
    static std::string name() { return "dtrmm"; }
};

struct dtrsm
{
    static std::string name() { return "dtrsm"; }
};

struct zgemm
{
    static std::string name() { return "zgemm"; }
};

struct dzgemm
{
    static std::string name() { return "dzgemm"; }
};

struct zgemm3m
{
    static std::string name() { return "zgemm3m"; }
};

struct zhemm
{
    static std::string name() { return "zhemm"; }
};

struct zher2k
{
    static std::string name() { return "zher2k"; }
};

struct zherk
{
    static std::string name() { return "zherk"; }
};

struct zsymm
{
    static std::string name() { return "zsymm"; }
};

struct zsyr2k
{
    static std::string name() { return "zsyr2k"; }
};

struct zsyrk
{
    static std::string name() { return "zsyrk"; }
};

struct ztrmm
{
    static std::string name() { return "ztrmm"; }
};

struct ztrsm
{
    static std::string name() { return "ztrsm"; }
};

void openblas_set_num_threads(int nbThreads);

float BlasInterface <OpenBlas, scabs1>::operator() (
    const std::complex<float> v0) const;

float BlasInterface <OpenBlas, sasum>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <OpenBlas, saxpy>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4, const int v5) const;

void BlasInterface <OpenBlas, saxpby>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <OpenBlas, saxpyi>::operator() (
    const int v0, const float v1, const float v2, const int v3, float v4) const;

float BlasInterface <OpenBlas, scasum>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

float BlasInterface <OpenBlas, scnrm2>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

void BlasInterface <OpenBlas, scopy>::operator() (
    const int v0, const float v1, const int v2, float v3, const int v4) const;

float BlasInterface <OpenBlas, sdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const;

float BlasInterface <OpenBlas, sdoti>::operator() (
    const int v0, const float v1, const int v2, const float v3) const;

float BlasInterface <OpenBlas, sdsdot>::operator() (
    const int v0, const float v1, const float v2, const int v3, const float v4, const int v5) const;

void BlasInterface <OpenBlas, sgthr>::operator() (
    const int v0, const float v1, float v2, const int v3) const;

void BlasInterface <OpenBlas, sgthrz>::operator() (
    const int v0, float v1, float v2, const int v3) const;

float BlasInterface <OpenBlas, snrm2>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <OpenBlas, srot>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5, const float v6) const;

void BlasInterface <OpenBlas, srotg>::operator() (
    float v0, float v1, float v2, float v3) const;

void BlasInterface <OpenBlas, sroti>::operator() (
    const int v0, float v1, const int v2, float v3, const float v4, const float v5) const;

void BlasInterface <OpenBlas, srotm>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4, const float v5) const;

void BlasInterface <OpenBlas, srotmg>::operator() (
    float v0, float v1, float v2, const float v3, float v4) const;

void BlasInterface <OpenBlas, sscal>::operator() (
    const int v0, const float v1, float v2, const int v3) const;

void BlasInterface <OpenBlas, ssctr>::operator() (
    const int v0, const float v1, const int v2, float v3) const;

void BlasInterface <OpenBlas, sswap>::operator() (
    const int v0, float v1, const int v2, float v3, const int v4) const;

int BlasInterface <OpenBlas, isamax>::operator() (
    const int v0, const float v1, const int v2) const;

int BlasInterface <OpenBlas, isamin>::operator() (
    const int v0, const float v1, const int v2) const;

void BlasInterface <OpenBlas, caxpy>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4, const int v5) const;

void BlasInterface <OpenBlas, caxpby>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <OpenBlas, caxpyi>::operator() (
    const int v0, const std::complex<float> v1, const std::complex<float> v2, const int v3, std::complex<float> v4) const;

void BlasInterface <OpenBlas, ccopy>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const;

void BlasInterface <OpenBlas, cgthr>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <OpenBlas, cgthrz>::operator() (
    const int v0, std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <OpenBlas, crotg>::operator() (
    std::complex<float> v0, const std::complex<float> v1, float v2, std::complex<float> v3) const;

void BlasInterface <OpenBlas, cscal>::operator() (
    const int v0, const std::complex<float> v1, std::complex<float> v2, const int v3) const;

void BlasInterface <OpenBlas, csctr>::operator() (
    const int v0, const std::complex<float> v1, const int v2, std::complex<float> v3) const;

void BlasInterface <OpenBlas, csrot>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4, const float v5, const float v6) const;

void BlasInterface <OpenBlas, csscal>::operator() (
    const int v0, const float v1, std::complex<float> v2, const int v3) const;

void BlasInterface <OpenBlas, cswap>::operator() (
    const int v0, std::complex<float> v1, const int v2, std::complex<float> v3, const int v4) const;

int BlasInterface <OpenBlas, icamax>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

int BlasInterface <OpenBlas, icamin>::operator() (
    const int v0, const std::complex<float> v1, const int v2) const;

double BlasInterface <OpenBlas, dcabs1>::operator() (
    const std::complex<double> v0) const;

double BlasInterface <OpenBlas, dasum>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <OpenBlas, daxpy>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4, const int v5) const;

void BlasInterface <OpenBlas, daxpby>::operator() (
    const int v0, const double v1, const double v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <OpenBlas, daxpyi>::operator() (
    const int v0, const double v1, const double v2, const int v3, double v4) const;

void BlasInterface <OpenBlas, dcopy>::operator() (
    const int v0, const double v1, const int v2, double v3, const int v4) const;

double BlasInterface <OpenBlas, ddot>::operator() (
    const int v0, const double v1, const int v2, const double v3, const int v4) const;

double BlasInterface <OpenBlas, dsdot>::operator() (
    const int v0, const float v1, const int v2, const float v3, const int v4) const;

double BlasInterface <OpenBlas, ddoti>::operator() (
    const int v0, const double v1, const int v2, const double v3) const;

void BlasInterface <OpenBlas, dgthr>::operator() (
    const int v0, const double v1, double v2, const int v3) const;

void BlasInterface <OpenBlas, dgthrz>::operator() (
    const int v0, double v1, double v2, const int v3) const;

double BlasInterface <OpenBlas, dnrm2>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <OpenBlas, drot>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5, const double v6) const;

void BlasInterface <OpenBlas, drotg>::operator() (
    double v0, double v1, double v2, double v3) const;

void BlasInterface <OpenBlas, droti>::operator() (
    const int v0, double v1, const int v2, double v3, const double v4, const double v5) const;

void BlasInterface <OpenBlas, drotm>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4, const double v5) const;

void BlasInterface <OpenBlas, drotmg>::operator() (
    double v0, double v1, double v2, const double v3, double v4) const;

void BlasInterface <OpenBlas, dscal>::operator() (
    const int v0, const double v1, double v2, const int v3) const;

void BlasInterface <OpenBlas, dsctr>::operator() (
    const int v0, const double v1, const int v2, double v3) const;

void BlasInterface <OpenBlas, dswap>::operator() (
    const int v0, double v1, const int v2, double v3, const int v4) const;

double BlasInterface <OpenBlas, dzasum>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

double BlasInterface <OpenBlas, dznrm2>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

int BlasInterface <OpenBlas, idamax>::operator() (
    const int v0, const double v1, const int v2) const;

int BlasInterface <OpenBlas, idamin>::operator() (
    const int v0, const double v1, const int v2) const;

void BlasInterface <OpenBlas, zaxpy>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4, const int v5) const;

void BlasInterface <OpenBlas, zaxpby>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <OpenBlas, zaxpyi>::operator() (
    const int v0, const std::complex<double> v1, const std::complex<double> v2, const int v3, std::complex<double> v4) const;

void BlasInterface <OpenBlas, zcopy>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const;

void BlasInterface <OpenBlas, zdrot>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4, const double v5, const double v6) const;

void BlasInterface <OpenBlas, zdscal>::operator() (
    const int v0, const double v1, std::complex<double> v2, const int v3) const;

void BlasInterface <OpenBlas, zgthr>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <OpenBlas, zgthrz>::operator() (
    const int v0, std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <OpenBlas, zrotg>::operator() (
    std::complex<double> v0, const std::complex<double> v1, double v2, std::complex<double> v3) const;

void BlasInterface <OpenBlas, zscal>::operator() (
    const int v0, const std::complex<double> v1, std::complex<double> v2, const int v3) const;

void BlasInterface <OpenBlas, zsctr>::operator() (
    const int v0, const std::complex<double> v1, const int v2, std::complex<double> v3) const;

void BlasInterface <OpenBlas, zswap>::operator() (
    const int v0, std::complex<double> v1, const int v2, std::complex<double> v3, const int v4) const;

int BlasInterface <OpenBlas, izamax>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

int BlasInterface <OpenBlas, izamin>::operator() (
    const int v0, const std::complex<double> v1, const int v2) const;

void BlasInterface <OpenBlas, sgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const;

void BlasInterface <OpenBlas, sgemv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const;

void BlasInterface <OpenBlas, sger>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <OpenBlas, ssbmv>::operator() (
    const char v0, const int v1, const int v2, const float v3, const float v4, const int v5, const float v6, const int v7, const float v8, float v9, const int v10) const;

void BlasInterface <OpenBlas, sspmv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const float v4, const int v5, const float v6, float v7, const int v8) const;

void BlasInterface <OpenBlas, sspr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5) const;

void BlasInterface <OpenBlas, sspr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7) const;

void BlasInterface <OpenBlas, ssymv>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, float v8, const int v9) const;

void BlasInterface <OpenBlas, ssyr>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, float v5, const int v6) const;

void BlasInterface <OpenBlas, ssyr2>::operator() (
    const char v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <OpenBlas, stbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <OpenBlas, stbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const float v5, const int v6, float v7, const int v8) const;

void BlasInterface <OpenBlas, stpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <OpenBlas, stpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, float v5, const int v6) const;

void BlasInterface <OpenBlas, strmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const;

void BlasInterface <OpenBlas, strsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const float v4, const int v5, float v6, const int v7) const;

void BlasInterface <OpenBlas, sgem2vu>::operator() (
    const int v0, const int v1, const float v2, const float v3, const int v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11, float v12, const int v13) const;

void BlasInterface <OpenBlas, cgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <OpenBlas, cgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <OpenBlas, cgerc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, cgeru>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, chbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <OpenBlas, chemv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const;

void BlasInterface <OpenBlas, cher>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5, const int v6) const;

void BlasInterface <OpenBlas, cher2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, chpmv>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const std::complex<float> v4, const int v5, const std::complex<float> v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, chpr>::operator() (
    const char v0, const int v1, const float v2, const std::complex<float> v3, const int v4, std::complex<float> v5) const;

void BlasInterface <OpenBlas, chpr2>::operator() (
    const char v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7) const;

void BlasInterface <OpenBlas, ctbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, ctbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<float> v5, const int v6, std::complex<float> v7, const int v8) const;

void BlasInterface <OpenBlas, ctpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <OpenBlas, ctpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, std::complex<float> v5, const int v6) const;

void BlasInterface <OpenBlas, ctrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const;

void BlasInterface <OpenBlas, ctrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<float> v4, const int v5, std::complex<float> v6, const int v7) const;

void BlasInterface <OpenBlas, cgem2vc>::operator() (
    const int v0, const int v1, const std::complex<float> v2, const std::complex<float> v3, const int v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11, std::complex<float> v12, const int v13) const;

void BlasInterface <OpenBlas, scgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<float> v3, const float v4, const int v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, std::complex<float> v9, const int v10) const;

void BlasInterface <OpenBlas, dgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const;

void BlasInterface <OpenBlas, dgemv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const;

void BlasInterface <OpenBlas, dger>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <OpenBlas, dsbmv>::operator() (
    const char v0, const int v1, const int v2, const double v3, const double v4, const int v5, const double v6, const int v7, const double v8, double v9, const int v10) const;

void BlasInterface <OpenBlas, dspmv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const double v4, const int v5, const double v6, double v7, const int v8) const;

void BlasInterface <OpenBlas, dspr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5) const;

void BlasInterface <OpenBlas, dspr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7) const;

void BlasInterface <OpenBlas, dsymv>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, double v8, const int v9) const;

void BlasInterface <OpenBlas, dsyr>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, double v5, const int v6) const;

void BlasInterface <OpenBlas, dsyr2>::operator() (
    const char v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <OpenBlas, dtbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <OpenBlas, dtbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const double v5, const int v6, double v7, const int v8) const;

void BlasInterface <OpenBlas, dtpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <OpenBlas, dtpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, double v5, const int v6) const;

void BlasInterface <OpenBlas, dtrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const;

void BlasInterface <OpenBlas, dtrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const double v4, const int v5, double v6, const int v7) const;

void BlasInterface <OpenBlas, dgem2vu>::operator() (
    const int v0, const int v1, const double v2, const double v3, const int v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11, double v12, const int v13) const;

void BlasInterface <OpenBlas, zgbmv>::operator() (
    const char v0, const int v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <OpenBlas, zgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <OpenBlas, zgerc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, zgeru>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, zhbmv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <OpenBlas, zhemv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const;

void BlasInterface <OpenBlas, zher>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5, const int v6) const;

void BlasInterface <OpenBlas, zher2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, zhpmv>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const std::complex<double> v4, const int v5, const std::complex<double> v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, zhpr>::operator() (
    const char v0, const int v1, const double v2, const std::complex<double> v3, const int v4, std::complex<double> v5) const;

void BlasInterface <OpenBlas, zhpr2>::operator() (
    const char v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7) const;

void BlasInterface <OpenBlas, ztbmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, ztbsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const int v4, const std::complex<double> v5, const int v6, std::complex<double> v7, const int v8) const;

void BlasInterface <OpenBlas, ztpmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <OpenBlas, ztpsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, std::complex<double> v5, const int v6) const;

void BlasInterface <OpenBlas, ztrmv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const;

void BlasInterface <OpenBlas, ztrsv>::operator() (
    const char v0, const char v1, const char v2, const int v3, const std::complex<double> v4, const int v5, std::complex<double> v6, const int v7) const;

void BlasInterface <OpenBlas, zgem2vc>::operator() (
    const int v0, const int v1, const std::complex<double> v2, const std::complex<double> v3, const int v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11, std::complex<double> v12, const int v13) const;

void BlasInterface <OpenBlas, dzgemv>::operator() (
    const char v0, const int v1, const int v2, const std::complex<double> v3, const double v4, const int v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, std::complex<double> v9, const int v10) const;

void BlasInterface <OpenBlas, sgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const float v5, const float v6, const int v7, const float v8, const int v9, const float v10, float v11, const int v12) const;

void BlasInterface <OpenBlas, ssymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const;

void BlasInterface <OpenBlas, ssyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, const int v8, const float v9, float v10, const int v11) const;

void BlasInterface <OpenBlas, ssyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const float v5, const int v6, const float v7, float v8, const int v9) const;

void BlasInterface <OpenBlas, strmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const;

void BlasInterface <OpenBlas, strsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const float v6, const float v7, const int v8, float v9, const int v10) const;

void BlasInterface <OpenBlas, cgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <OpenBlas, scgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const float v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <OpenBlas, cgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<float> v5, const std::complex<float> v6, const int v7, const std::complex<float> v8, const int v9, const std::complex<float> v10, std::complex<float> v11, const int v12) const;

void BlasInterface <OpenBlas, chemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <OpenBlas, cher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const float v9, std::complex<float> v10, const int v11) const;

void BlasInterface <OpenBlas, cherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const float v4, const std::complex<float> v5, const int v6, const float v7, std::complex<float> v8, const int v9) const;

void BlasInterface <OpenBlas, csymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <OpenBlas, csyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, const int v8, const std::complex<float> v9, std::complex<float> v10, const int v11) const;

void BlasInterface <OpenBlas, csyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<float> v4, const std::complex<float> v5, const int v6, const std::complex<float> v7, std::complex<float> v8, const int v9) const;

void BlasInterface <OpenBlas, ctrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const;

void BlasInterface <OpenBlas, ctrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<float> v6, const std::complex<float> v7, const int v8, std::complex<float> v9, const int v10) const;

void BlasInterface <OpenBlas, dgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const double v5, const double v6, const int v7, const double v8, const int v9, const double v10, double v11, const int v12) const;

void BlasInterface <OpenBlas, dsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const;

void BlasInterface <OpenBlas, dsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, const int v8, const double v9, double v10, const int v11) const;

void BlasInterface <OpenBlas, dsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const double v5, const int v6, const double v7, double v8, const int v9) const;

void BlasInterface <OpenBlas, dtrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const;

void BlasInterface <OpenBlas, dtrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const double v6, const double v7, const int v8, double v9, const int v10) const;

void BlasInterface <OpenBlas, zgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <OpenBlas, dzgemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const double v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <OpenBlas, zgemm3m>::operator() (
    const char v0, const char v1, const int v2, const int v3, const int v4, const std::complex<double> v5, const std::complex<double> v6, const int v7, const std::complex<double> v8, const int v9, const std::complex<double> v10, std::complex<double> v11, const int v12) const;

void BlasInterface <OpenBlas, zhemm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <OpenBlas, zher2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const double v9, std::complex<double> v10, const int v11) const;

void BlasInterface <OpenBlas, zherk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const double v4, const std::complex<double> v5, const int v6, const double v7, std::complex<double> v8, const int v9) const;

void BlasInterface <OpenBlas, zsymm>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <OpenBlas, zsyr2k>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, const int v8, const std::complex<double> v9, std::complex<double> v10, const int v11) const;

void BlasInterface <OpenBlas, zsyrk>::operator() (
    const char v0, const char v1, const int v2, const int v3, const std::complex<double> v4, const std::complex<double> v5, const int v6, const std::complex<double> v7, std::complex<double> v8, const int v9) const;

void BlasInterface <OpenBlas, ztrmm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const;

void BlasInterface <OpenBlas, ztrsm>::operator() (
    const char v0, const char v1, const char v2, const char v3, const int v4, const int v5, const std::complex<double> v6, const std::complex<double> v7, const int v8, std::complex<double> v9, const int v10) const;

std::complex<float> BlasInterface <OpenBlas, cdotc>::operator() (
    const int v0, const std::complex<float> v1, const int v2, const std::complex<float> v3, const int v4) const;

std::complex<float> BlasInterface <OpenBlas, cdotu>::operator() (
    const int v0, const std::complex<float> v1, const int v2, const std::complex<float> v3, const int v4) const;

std::complex<double> BlasInterface <OpenBlas, zdotc>::operator() (
    const int v0, const std::complex<double> v1, const int v2, const std::complex<double> v3, const int v4) const;

std::complex<double> BlasInterface <OpenBlas, zdotu>::operator() (
    const int v0, const std::complex<double> v1, const int v2, const std::complex<double> v3, const int v4) const;

} // namespace BlasBooster