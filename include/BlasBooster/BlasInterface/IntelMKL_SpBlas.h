#pragma once

extern "C" {

void mkl_dcsrmm(const char*, const int*, const int*, const int*, const double*, const char*, const double*, const int*, const int*, const int*, const double*, const int*, const double*, double*, const int*);
void mkl_dcsrmultcsr(const char*, const int*, const int*, const int*, const int*, const int*, double*, int*, int*, double*, int*, int*, double*, int*, int*, const int*, int*);
void mkl_scsrmm(const char*, const int*, const int*, const int*, const float*, const char*, const float*, const int*, const int*, const int*, const float*, const int*, const float*, float*, const int*);
void mkl_scsrmultcsr(const char*, const int*, const int*, const int*, const int*, const int*, float*, int*, int*, float*, int*, int*, float*, int*, int*, const int*, int*);

} // extern "C"