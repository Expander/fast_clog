#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// fast implementation of complex logarithm in C
void fast_clog(double re, double im, double* out_re, double* out_im);

/// fast implementation of complex logarithm in Fortran
void fast_clog_(const double* re, const double* im, double* out_re, double* out_im);

#ifdef __cplusplus
}
#endif
