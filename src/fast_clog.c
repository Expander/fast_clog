#include <complex.h>
#include <math.h>


static double _Complex fast_clog_(double _Complex z)
{
   const double rz = creal(z);
   const double iz = cimag(z);

   return 0.5*log(rz*rz + iz*iz) + I*atan2(iz, rz);
}


void fast_clog(double re, double im, double* res_re, double* res_im)
{
   const double _Complex res = fast_clog_(re + I*im);
   *res_re = creal(res);
   *res_im = cimag(res);
}