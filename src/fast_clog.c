#include <complex.h>
#include <math.h>


static double _Complex fast_clog_c99(double _Complex z)
{
   const double rz = creal(z);
   const double iz = cimag(z);

   return 0.5*log(rz*rz + iz*iz) + I*atan2(iz, rz);
}


void fast_clog(double re, double im, double* out_re, double* out_im)
{
   *out_re = 0.5*log(re*re + im*im);
   *out_im = atan2(im, re);
}
