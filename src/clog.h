#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// complex logarithm in Fortran
void clog_(const double* re, const double* im, double* out_re, double* out_im);

#ifdef __cplusplus
}
#endif
