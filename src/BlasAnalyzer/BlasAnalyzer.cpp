#include "ReportManager.h"
#include "DenseMatrix.h"
#include "IntelMKL.h"
#include "Multiplication.h"
#include <boost/timer/timer.hpp>

using namespace BlasBooster;

extern "C" {

int dgemm_(char *transa, char *transb, int *m, int *n, int *k,
           double *alpha, double *a, int *lda, double *b, int *ldb,
           double *beta, double *c, int *ldc)
{
    ReportManager reportManager(dgemm);
    //reportManager.registerValue(transa,*transa);

    DenseMatrix<double> A(*m,*k,a);
    //if ( toUpper(*transa) == 'T' ) transpose(ptrA);
    reportManager.registerMatrix(A,"Matrix_A");

    DenseMatrix<double> B(*k,*n,b);
    //if ( toUpper(*transb) == 'T' ) transpose(B);
    reportManager.registerMatrix(B,"Matrix_B");

    DenseMatrix<double> C(*m,*n,c);
    mult(C,A,B);
    reportManager.registerMatrix(C,"Matrix_C");

    boost::timer::cpu_timer timer;
    IntelMKL::dgemm(transa,transb,m,n,k,alpha,a,lda,b,ldb,beta,c,ldc);
    reportManager.registerTime(timer.format());
}

int sgemm_(char *transa, char *transb, int *m, int *n, int *k,
           float *alpha, float *a, int *lda, float *b, int *ldb,
           float *beta, float *c, int *ldc)
{
    ReportManager reportManager(sgemm);

    DenseMatrix<float> A(*m,*k,a);
    DenseMatrix<float> B(*k,*n,b);
    DenseMatrix<float> C(*m,*n,c);
    mult(C,A,B);
}

} // end extern "C"
