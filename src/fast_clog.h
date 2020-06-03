#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// fast implementation of complex logarithm
void fast_clog(double re, double im, double* res_re, double* res_im);

#ifdef __cplusplus
}
#endif
