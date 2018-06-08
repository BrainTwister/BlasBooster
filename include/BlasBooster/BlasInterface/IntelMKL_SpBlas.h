#pragma once

extern "C" {

void mkl_dcsrmm_(const char*, const int*, const int*, const int*, const double*, const char*, const double*, const int*, const int*, const int*, const double*, const int*, const double*, double*, const int*);
void mkl_dcsrmultcsr_(const char*, const int*, const int*, const int*, const int*, const int*, double*, int*, int*, double*, int*, int*, double*, int*, int*, const int*, int*);

} // extern "C"