#ifndef BLASBOOSTERMACROBLASFUNCTIONLIST_H_
#define BLASBOOSTERMACROBLASFUNCTIONLIST_H_

#include <complex>

#define BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT\
    (( float,  scabs1,  (const std::complex<float>) ))\
    (( float,  sasum,   (const int)(const float)(const int) ))\
    (( void,   saxpy,   (const int)(const float)(const float)(const int)(float)(const int) ))\
    (( void,   saxpby,  (const int)(const float)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   saxpyi,  (const int)(const float)(const float)(const int)(float) ))\
    (( float,  scasum,  (const int)(const std::complex<float>)(const int) ))\
    (( float,  scnrm2,  (const int)(const std::complex<float>)(const int) ))\
    (( void,   scopy,   (const int)(const float)(const int)(float)(const int) ))\
    (( float,  sdot,    (const int)(const float)(const int)(const float)(const int) ))\
    (( float,  sdoti,   (const int)(const float)(const int)(const float) ))\
    (( float,  sdsdot,  (const int)(const float)(const float)(const int)(const float)(const int) ))\
    (( void,   sgthr,   (const int)(const float)(float)(const int) ))\
    (( void,   sgthrz,  (const int)(float)(float)(const int) ))\
    (( float,  snrm2,   (const int)(const float)(const int) ))\
    (( void,   srot,    (const int)(float)(const int)(float)(const int)(const float)(const float) ))\
    (( void,   srotg,   (float)(float)(float)(float) ))\
    (( void,   sroti,   (const int)(float)(const int)(float)(const float)(const float) ))\
    (( void,   srotm,   (const int)(float)(const int)(float)(const int)(const float) ))\
    (( void,   srotmg,  (float)(float)(float)(const float)(float) ))\
    (( void,   sscal,   (const int)(const float)(float)(const int) ))\
    (( void,   ssctr,   (const int)(const float)(const int)(float) ))\
    (( void,   sswap,   (const int)(float)(const int)(float)(const int) ))\
    (( int,    isamax,  (const int)(const float)(const int) ))\
    (( int,    isamin,  (const int)(const float)(const int) ))\
    (( void,   caxpy,   (const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   caxpby,  (const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   caxpyi,  (const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( void,   ccopy,   (const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   cgthr,   (const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cgthrz,  (const int)(std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   crotg,   (std::complex<float>)(const std::complex<float>)(float)(std::complex<float>) ))\
    (( void,   cscal,   (const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   csctr,   (const int)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( void,   csrot,   (const int)(std::complex<float>)(const int)(std::complex<float>)(const int)(const float)(const float) ))\
    (( void,   csscal,  (const int)(const float)(std::complex<float>)(const int) ))\
    (( void,   cswap,   (const int)(std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( int,    icamax,  (const int)(const std::complex<float>)(const int) ))\
    (( int,    icamin,  (const int)(const std::complex<float>)(const int) ))\
    (( double, dcabs1,  (const std::complex<double>) ))\
    (( double, dasum,   (const int)(const double)(const int) ))\
    (( void,   daxpy,   (const int)(const double)(const double)(const int)(double)(const int) ))\
    (( void,   daxpby,  (const int)(const double)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   daxpyi,  (const int)(const double)(const double)(const int)(double) ))\
    (( void,   dcopy,   (const int)(const double)(const int)(double)(const int) ))\
    (( double, ddot,    (const int)(const double)(const int)(const double)(const int) ))\
    (( double, dsdot,   (const int)(const float)(const int)(const float)(const int) ))\
    (( double, ddoti,   (const int)(const double)(const int)(const double) ))\
    (( void,   dgthr,   (const int)(const double)(double)(const int) ))\
    (( void,   dgthrz,  (const int)(double)(double)(const int) ))\
    (( double, dnrm2,   (const int)(const double)(const int) ))\
    (( void,   drot,    (const int)(double)(const int)(double)(const int)(const double)(const double) ))\
    (( void,   drotg,   (double)(double)(double)(double) ))\
    (( void,   droti,   (const int)(double)(const int)(double)(const double)(const double) ))\
    (( void,   drotm,   (const int)(double)(const int)(double)(const int)(const double) ))\
    (( void,   drotmg,  (double)(double)(double)(const double)(double) ))\
    (( void,   dscal,   (const int)(const double)(double)(const int) ))\
    (( void,   dsctr,   (const int)(const double)(const int)(double) ))\
    (( void,   dswap,   (const int)(double)(const int)(double)(const int) ))\
    (( double, dzasum,  (const int)(const std::complex<double>)(const int) ))\
    (( double, dznrm2,  (const int)(const std::complex<double>)(const int) ))\
    (( int,    idamax,  (const int)(const double)(const int) ))\
    (( int,    idamin,  (const int)(const double)(const int) ))\
    (( void,   zaxpy,   (const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zaxpby,  (const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zaxpyi,  (const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( void,   zcopy,   (const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zdrot,   (const int)(std::complex<double>)(const int)(std::complex<double>)(const int)(const double)(const double) ))\
    (( void,   zdscal,  (const int)(const double)(std::complex<double>)(const int) ))\
    (( void,   zgthr,   (const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zgthrz,  (const int)(std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zrotg,   (std::complex<double>)(const std::complex<double>)(double)(std::complex<double>) ))\
    (( void,   zscal,   (const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zsctr,   (const int)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( void,   zswap,   (const int)(std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( int,    izamax,  (const int)(const std::complex<double>)(const int) ))\
    (( int,    izamin,  (const int)(const std::complex<double>)(const int) ))\
    (( void,   sgbmv,   (const char)(const int)(const int)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   sgemv,   (const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   sger,    (const int)(const int)(const float)(const float)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   ssbmv,   (const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   sspmv,   (const char)(const int)(const float)(const float)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   sspr,    (const char)(const int)(const float)(const float)(const int)(float) ))\
    (( void,   sspr2,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(float) ))\
    (( void,   ssymv,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   ssyr,    (const char)(const int)(const float)(const float)(const int)(float)(const int) ))\
    (( void,   ssyr2,   (const char)(const int)(const float)(const float)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   stbmv,   (const char)(const char)(const char)(const int)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   stbsv,   (const char)(const char)(const char)(const int)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   stpmv,   (const char)(const char)(const char)(const int)(const float)(float)(const int) ))\
    (( void,   stpsv,   (const char)(const char)(const char)(const int)(const float)(float)(const int) ))\
    (( void,   strmv,   (const char)(const char)(const char)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   strsv,   (const char)(const char)(const char)(const int)(const float)(const int)(float)(const int) ))\
    (( void,   sgem2vu, (const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(const int)(const float)(float)(const int)(float)(const int) ))\
    (( void,   cgbmv,   (const char)(const int)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cgemv,   (const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cgerc,   (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   cgeru,   (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   chbmv,   (const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   chemv,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cher,    (const char)(const int)(const float)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   cher2,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   chpmv,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   chpr,    (const char)(const int)(const float)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( void,   chpr2,   (const char)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(std::complex<float>) ))\
    (( void,   ctbmv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   ctbsv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   ctpmv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   ctpsv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   ctrmv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   ctrsv,   (const char)(const char)(const char)(const int)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   cgem2vc, (const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   scgemv,  (const char)(const int)(const int)(const std::complex<float>)(const float)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   dgbmv,   (const char)(const int)(const int)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dgemv,   (const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dger,    (const int)(const int)(const double)(const double)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dsbmv,   (const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dspmv,   (const char)(const int)(const double)(const double)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dspr,    (const char)(const int)(const double)(const double)(const int)(double) ))\
    (( void,   dspr2,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(double) ))\
    (( void,   dsymv,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dsyr,    (const char)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( void,   dsyr2,   (const char)(const int)(const double)(const double)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dtbmv,   (const char)(const char)(const char)(const int)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dtbsv,   (const char)(const char)(const char)(const int)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dtpmv,   (const char)(const char)(const char)(const int)(const double)(double)(const int) ))\
    (( void,   dtpsv,   (const char)(const char)(const char)(const int)(const double)(double)(const int) ))\
    (( void,   dtrmv,   (const char)(const char)(const char)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dtrsv,   (const char)(const char)(const char)(const int)(const double)(const int)(double)(const int) ))\
    (( void,   dgem2vu, (const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(const int)(const double)(double)(const int)(double)(const int) ))\
    (( void,   zgbmv,   (const char)(const int)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zgemv,   (const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zgerc,   (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zgeru,   (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zhbmv,   (const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zhemv,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zher,    (const char)(const int)(const double)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zher2,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zhpmv,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zhpr,    (const char)(const int)(const double)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( void,   zhpr2,   (const char)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(std::complex<double>) ))\
    (( void,   ztbmv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   ztbsv,   (const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   ztpmv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   ztpsv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   ztrmv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   ztrsv,   (const char)(const char)(const char)(const int)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   zgem2vc, (const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   dzgemv,  (const char)(const int)(const int)(const std::complex<double>)(const double)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   sgemm,   (const char)(const char)(const int)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   ssymm,   (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   ssyr2k,  (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   ssyrk,   (const char)(const char)(const int)(const int)(const float)(const float)(const int)(const float)(float)(const int) ))\
    (( void,   strmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const float)(const float)(const int)(float)(const int) ))\
    (( void,   strsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const float)(const float)(const int)(float)(const int) ))\
    (( void,   cgemm,   (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   scgemm,  (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const float)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cgemm3m, (const char)(const char)(const int)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   chemm,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   cher2k,  (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const float)(std::complex<float>)(const int) ))\
    (( void,   cherk,   (const char)(const char)(const int)(const int)(const float)(const std::complex<float>)(const int)(const float)(std::complex<float>)(const int) ))\
    (( void,   csymm,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   csyr2k,  (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   csyrk,   (const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(const std::complex<float>)(std::complex<float>)(const int) ))\
    (( void,   ctrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   ctrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<float>)(const std::complex<float>)(const int)(std::complex<float>)(const int) ))\
    (( void,   dgemm,   (const char)(const char)(const int)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dsymm,   (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dsyr2k,  (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dsyrk,   (const char)(const char)(const int)(const int)(const double)(const double)(const int)(const double)(double)(const int) ))\
    (( void,   dtrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( void,   dtrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const double)(const double)(const int)(double)(const int) ))\
    (( void,   zgemm,   (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   dzgemm,  (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const double)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zgemm3m, (const char)(const char)(const int)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zhemm,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zher2k,  (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const double)(std::complex<double>)(const int) ))\
    (( void,   zherk,   (const char)(const char)(const int)(const int)(const double)(const std::complex<double>)(const int)(const double)(std::complex<double>)(const int) ))\
    (( void,   zsymm,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zsyr2k,  (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   zsyrk,   (const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(const std::complex<double>)(std::complex<double>)(const int) ))\
    (( void,   ztrmm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))\
    (( void,   ztrsm,   (const char)(const char)(const char)(const char)(const int)(const int)(const std::complex<double>)(const std::complex<double>)(const int)(std::complex<double>)(const int) ))

#define BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_WITH_RETURN\
    (( std::complex<float>,  cdotc, (const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    (( std::complex<float>,  cdotu, (const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    (( std::complex<double>, zdotc, (const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
    (( std::complex<double>, zdotu, (const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\

#define BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_NO_RETURN\
    (( void, cdotc, (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    (( void, cdotu, (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
    (( void, zdotc, (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
    (( void, zdotu, (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\

#define BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST\
	BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_WITHOUT_ZDOT\
	BLASBOOSTER_MACRO_BLAS_FUNCTION_LIST_ZDOT_WITH_RETURN

//(( void,   cdotc,   (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
//(( void,   cdotci,  (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>) ))\
//(( void,   cdotu,   (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>)(const int) ))\
//(( void,   cdotui,  (std::complex<float>)(const int)(const std::complex<float>)(const int)(const std::complex<float>) ))\
//(( void,   zdotc,   (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
//(( void,   zdotci,  (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>) ))\
//(( void,   zdotu,   (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>)(const int) ))\
//(( void,   zdotui,  (std::complex<double>)(const int)(const std::complex<double>)(const int)(const std::complex<double>) ))\

#endif /* BLASBOOSTERMACROBLASFUNCTIONLIST_H_ */
