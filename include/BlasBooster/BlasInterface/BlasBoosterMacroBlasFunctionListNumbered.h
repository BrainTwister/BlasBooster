#ifndef BLASBOOSTERMACROBLASFUNCTIONLIST_H_
#define BLASBOOSTERMACROBLASFUNCTIONLIST_H_

#include <complex>

#define BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST\
    ((   0, float,  scabs1,  (const std::complex<float>) ))\
    ((   1, float,  sasum,   (const int)(const float)(const int) ))\
    ((   2, void,   saxpy,   (const int)(const float)(const float)(const int)(float)(const int) ))\
    ((   3, void,   saxpby,  (const int)(const float)(const float)(const int)(const float)(float)(const int) ))\
    ((   4, void,   saxpyi,  (const int)(const float)(const float)(const int)(float) ))\
    ((   5, float,  scasum,  (const int)(const std::complex<float>)(const int) ))\
    ((   6, float,  scnrm2,  (const int)(const std::complex<float>)(const int) ))\
    ((   7, void,   scopy,   (const int)(const float)(const int)(float)(const int) ))\
    ((   8, float,  sdot,    (const int)(const float)(const int)(const float)(const int) ))\
    ((   9, float,  sdoti,   (const int)(const float)(const int)(const float) ))\
    ((  10, float,  sdsdot,  (const int)(const float)(const float)(const int)(const float)(const int) ))\
    ((  11, void,   sgthr,   (const int)(const float)(float)(const int) ))\
    ((  12, void,   sgthrz,  (const int)(float)(float)(const int) ))\
    ((  13, float,  snrm2,   (const int)(const float)(const int) ))\
    ((  14, void,   srot,    (const int)(float)(const int)(float)(const int)(const float)(const float) ))\
    ((  15, void,   srotg,   (float)(float)(float)(float) ))\
    ((  16, void,   sroti,   (const int)(float)(const int)(float)(const float)(const float) ))\
    ((  17, void,   srotm,   (const int)(float)(const int)(float)(const int)(const float) ))\
    ((  18, void,   srotmg,  (float)(float)(float)(const float)(float) ))\
    ((  19, void,   sscal,   (const int)(const float)(float)(const int) ))\
    ((  20, void,   ssctr,   (const int)(const float)(const int)(float) ))\
    ((  21, void,   sswap,   (const int)(float)(const int)(float)(const int) ))\
    ((  22, int,    isamax,  (const int)(const float)(const int) ))\
    ((  23, int,    isamin,  (const int)(const float)(const int) ))\
    ((  24, void,   caxpy,   (const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    ((  25, void,   caxpby,  (const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    ((  26, void,   caxpyi,  (const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>) ))\
    ((  27, void,   ccopy,   (const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    ((  28, std::complex<float>,   cdotc,   (const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    ((  29, std::complex<float>,   cdotu,   (const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    ((  30, void,   cgthr,   (const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    ((  31, void,   cgthrz,  (const int)(std::complex<float>)(std::complex<float>)(const int) ))\
    ((  32, void,   crotg,   (std::complex<float>)(const std::complex<float>)(float)(std::complex<float>) ))\
    ((  33, void,   cscal,   (const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    ((  34, void,   csctr,   (const int)(const std::complex<float>)(const int)(std::complex<float>) ))\
    ((  35, void,   csrot,   (const int)(std::complex<float>)(const int)(std::complex<float>)(const int)(const float)(const float) ))\
    ((  36, void,   csscal,  (const int)(const float)(std::complex<float>)(const int) ))\
    ((  37, void,   cswap,   (const int)(std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    ((  38, int,    icamax,  (const int)(const std::complex<float>)(const int) ))\
    ((  39, int,    icamin,  (const int)(const std::complex<float>)(const int) ))\
    ((  40, double, dcabs1,  (const std::complex<double>) ))\
    ((  41, double, dasum,   (const int)(const double)(const int) ))\
    ((  42, void,   daxpy,   (const int)(const double)(const double)(const int)(double)(const int) ))\
    ((  43, void,   daxpby,  (const int)(const double)(const double)(const int)(const double)(double)(const int) ))\
    ((  44, void,   daxpyi,  (const int)(const double)(const double)(const int)(double) ))\
    ((  45, void,   dcopy,   (const int)(const double)(const int)(double)(const int) ))\
    ((  46, double, ddot,    (const int)(const double)(const int)(const double)(const int) ))\
    ((  47, double, dsdot,   (const int)(const float)(const int)(const float)(const int) ))\
    ((  48, double, ddoti,   (const int)(const double)(const int)(const double) ))\
    ((  49, void,   dgthr,   (const int)(const double)(double)(const int) ))\
    ((  50, void,   dgthrz,  (const int)(double)(double)(const int) ))\
    ((  51, double, dnrm2,   (const int)(const double)(const int) ))\
    ((  52, void,   drot,    (const int)(double)(const int)(double)(const int)(const double)(const double) ))\
    ((  53, void,   drotg,   (double)(double)(double)(double) ))\
    ((  54, void,   droti,   (const int)(double)(const int)(double)(const double)(const double) ))\
    ((  55, void,   drotm,   (const int)(double)(const int)(double)(const int)(const double) ))\
    ((  56, void,   drotmg,  (double)(double)(double)(const double)(double) ))\
    ((  57, void,   dscal,   (const int)(const double)(double)(const int) ))\
    ((  58, void,   dsctr,   (const int)(const double)(const int)(double) ))\
    ((  59, void,   dswap,   (const int)(double)(const int)(double)(const int) ))\
    ((  60, double, dzasum,  (const int)(const std::complex<double>)(const int) ))\
    ((  61, double, dznrm2,  (const int)(const std::complex<double>)(const int) ))\
    ((  62, int,    idamax,  (const int)(const double)(const int) ))\
    ((  63, int,    idamin,  (const int)(const double)(const int) ))\
    ((  64, void,   zaxpy,   (const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    ((  65, void,   zaxpby,  (const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    ((  66, void,   zaxpyi,  (const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>) ))\
    ((  67, void,   zcopy,   (const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    ((  68, std::complex<double>,   zdotc,   (const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
    ((  69, std::complex<double>,   zdotu,   (const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
    ((  70, void,   zdrot,   (const int)(std::complex<double>)(const int)(std::complex<double>)(const int)(const double)(const double) ))\
    ((  71, void,   zdscal,  (const int)(const double)(std::complex<double>)(const int) ))\
    ((  72, void,   zgthr,   (const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    ((  73, void,   zgthrz,  (const int)(std::complex<double>)(std::complex<double>)(const int) ))\
    ((  74, void,   zrotg,   (std::complex<double>)(const std::complex<double>)(double)(std::complex<double>) ))\
    ((  75, void,   zscal,   (const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    ((  76, void,   zsctr,   (const int)(const std::complex<double>)(const int)(std::complex<double>) ))\
    ((  77, void,   zswap,   (const int)(std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    ((  78, int,    izamax,  (const int)(const std::complex<double>)(const int) ))\
    ((  79, int,    izamin,  (const int)(const std::complex<double>)(const int) ))\
    ((  80, void,   sgbmv,   (const char)(const int)(const int)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    ((  81, void,   sgemv,   (const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    ((  82, void,   sger,    (const int)(const int)(const float)(const float)(const int)(const float)(const int)(float)(const int) ))\
    ((  83, void,   ssbmv,   (const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    ((  84, void,   sspmv,   (const char)(const int)(const float)(const float)(const float)(const int)(const float)(float)(const int) ))\
    ((  85, void,   sspr,    (const char)(const int)(const float)(const float)(const int)(float) ))\
    ((  86, void,   sspr2,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(float) ))\
    ((  87, void,   ssymv,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    ((  88, void,   ssyr,    (const char)(const int)(const float)(const float)(const int)(float)(const int) ))\
    ((  89, void,   ssyr2,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(float)(const int) ))\
    ((  90, void,   stbmv,   (const char)(const char)(const char)(const int)(const int)(const float)(const int)(float)(const int) ))\
    ((  91, void,   stbsv,   (const char)(const char)(const char)(const int)(const int)(const float)(const int)(float)(const int) ))\
    ((  92, void,   stpmv,   (const char)(const char)(const char)(const int)(const float)(float)(const int) ))\
    ((  93, void,   stpsv,   (const char)(const char)(const char)(const int)(const float)(float)(const int) ))\
    ((  94, void,   strmv,   (const char)(const char)(const char)(const int)(const float)(const int)(float)(const int) ))\
    ((  95, void,   strsv,   (const char)(const char)(const char)(const int)(const float)(const int)(float)(const int) ))\
    ((  96, void,   sgem2vu, (const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(const int)(const float)(float)(const int)(float)(const int) ))\
    ((  97, void,   cgbmv,   (const char)(const int)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    ((  98, void,   cgemv,   (const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    ((  99, void,   cgerc,   (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 100, void,   cgeru,   (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 101, void,   chbmv,   (const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 102, void,   chemv,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 103, void,   cher,    (const char)(const int)(const float)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 104, void,   cher2,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 105, void,   chpmv,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 106, void,   chpr,    (const char)(const int)(const float)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( 107, void,   chpr2,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( 108, void,   ctbmv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 109, void,   ctbsv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 110, void,   ctpmv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 111, void,   ctpsv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 112, void,   ctrmv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 113, void,   ctrsv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 114, void,   cgem2vc, (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 115, void,   scgemv,  (const char)(const int)(const int)(const std::complex<float>)(const float)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 116, void,   dgbmv,   (const char)(const int)(const int)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 117, void,   dgemv,   (const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 118, void,   dger,    (const int)(const int)(const double)(const double)(const int)(const double)(const int)(double)(const int) ))\
    (( 119, void,   dsbmv,   (const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 120, void,   dspmv,   (const char)(const int)(const double)(const double)(const double)(const int)(const double)(double)(const int) ))\
    (( 121, void,   dspr,    (const char)(const int)(const double)(const double)(const int)(double) ))\
    (( 122, void,   dspr2,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(double) ))\
    (( 123, void,   dsymv,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 124, void,   dsyr,    (const char)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( 125, void,   dsyr2,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(double)(const int) ))\
    (( 126, void,   dtbmv,   (const char)(const char)(const char)(const int)(const int)(const double)(const int)(double)(const int) ))\
    (( 127, void,   dtbsv,   (const char)(const char)(const char)(const int)(const int)(const double)(const int)(double)(const int) ))\
    (( 128, void,   dtpmv,   (const char)(const char)(const char)(const int)(const double)(double)(const int) ))\
    (( 129, void,   dtpsv,   (const char)(const char)(const char)(const int)(const double)(double)(const int) ))\
    (( 130, void,   dtrmv,   (const char)(const char)(const char)(const int)(const double)(const int)(double)(const int) ))\
    (( 131, void,   dtrsv,   (const char)(const char)(const char)(const int)(const double)(const int)(double)(const int) ))\
    (( 132, void,   dgem2vu, (const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(const int)(const double)(double)(const int)(double)(const int) ))\
    (( 133, void,   zgbmv,   (const char)(const int)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 134, void,   zgemv,   (const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 135, void,   zgerc,   (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 136, void,   zgeru,   (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 137, void,   zhbmv,   (const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 138, void,   zhemv,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 139, void,   zher,    (const char)(const int)(const double)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 140, void,   zher2,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 141, void,   zhpmv,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 142, void,   zhpr,    (const char)(const int)(const double)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( 143, void,   zhpr2,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( 144, void,   ztbmv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 145, void,   ztbsv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 146, void,   ztpmv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 147, void,   ztpsv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 148, void,   ztrmv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 149, void,   ztrsv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 150, void,   zgem2vc, (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 151, void,   dzgemv,  (const char)(const int)(const int)(const std::complex<double>)(const double)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 152, void,   sgemm,   (const char)(const char)(const int)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( 153, void,   ssymm,   (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( 154, void,   ssyr2k,  (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( 155, void,   ssyrk,   (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(float)(const int) ))\
    (( 156, void,   strmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const float)(const float)(const int)(float)(const int) ))\
    (( 157, void,   strsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const float)(const float)(const int)(float)(const int) ))\
    (( 158, void,   cgemm,   (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 159, void,   scgemm,  (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const float)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 160, void,   cgemm3m, (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 161, void,   chemm,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 162, void,   cher2k,  (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const float)(std::complex<float>)(const int) ))\
    (( 163, void,   cherk,   (const char)(const char)(const int)(const int)(const float)(const std::complex<float>)(const int)(const float)(std::complex<float>)(const int) ))\
    (( 164, void,   csymm,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 165, void,   csyr2k,  (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 166, void,   csyrk,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( 167, void,   ctrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 168, void,   ctrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( 169, void,   dgemm,   (const char)(const char)(const int)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 170, void,   dsymm,   (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 171, void,   dsyr2k,  (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( 172, void,   dsyrk,   (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(double)(const int) ))\
    (( 173, void,   dtrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( 174, void,   dtrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( 175, void,   zgemm,   (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 176, void,   dzgemm,  (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const double)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 177, void,   zgemm3m, (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 178, void,   zhemm,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 179, void,   zher2k,  (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const double)(std::complex<double>)(const int) ))\
    (( 180, void,   zherk,   (const char)(const char)(const int)(const int)(const double)(const std::complex<double>)(const int)(const double)(std::complex<double>)(const int) ))\
    (( 181, void,   zsymm,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 182, void,   zsyr2k,  (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 183, void,   zsyrk,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( 184, void,   ztrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( 185, void,   ztrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))
// BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST

//(( void,   cdotc,   (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
//(( void,   cdotci,  (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>) ))\
//(( void,   cdotu,   (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
//(( void,   cdotui,  (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>) ))\
//(( void,   zdotc,   (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
//(( void,   zdotci,  (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>) ))\
//(( void,   zdotu,   (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
//(( void,   zdotui,  (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>) ))\

#endif /* BLASBOOSTERMACROBLASFUNCTIONLIST_H_ */
