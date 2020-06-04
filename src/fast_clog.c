#include <math.h>


void fast_clog(double re, double im, double* out_re, double* out_im)
{
   *out_re = 0.5*log(re*re + im*im);
   *out_im = atan2(im, re);
}
