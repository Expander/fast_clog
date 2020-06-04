#include "fast_clog.h"
#include "fast_clog.hpp"
#include <iostream>
#include <limits>
#include <complex>


unsigned errors = 0;


bool is_equal(const std::complex<double>& a, const std::complex<double>& b, double eps)
{
   return std::real(a - b) <= eps && std::imag(a - b) <= eps;
}


#define CHECK_EQ(lhs,rhs,eps)                                           \
   do {                                                                 \
      if (!is_equal(lhs, rhs, eps)) {                                   \
         std::cerr << "FAILED test in line " << __LINE__                \
                   << ": lhs (" << lhs << ") != rhs (" << rhs << ")" << std::endl; \
         errors++;                                                      \
      }                                                                 \
   } while (0)


std::complex<double> fast_clog_c(const std::complex<double>& z)
{
   double re, im;
   fast_clog(std::real(z), std::imag(z), &re, &im);
   return { re, im };
}


std::complex<double> fast_clog_f(const std::complex<double>& z)
{
   const double re = std::real(z), im = std::imag(z);
   double out_re, out_im;
   fast_clog_(&re, &im, &out_re, &out_im);
   return { out_re, out_im };
}


void test_fast_clog()
{
   const double eps = std::numeric_limits<double>::epsilon();
   const double eul = 2.7182818284590452354;
   const std::complex<double> numbers[] = {
      {-1.0,  0.0},
      {-1.0, -0.0},
      { 1.0,  0.0},
      { 1.0, -0.0},
      { 0.0,  1.0},
      { 2.0,  0.0},
      { 0.0,  2.0},
      { 1.0,  1.0},
      { 2.0,  1.0},
      { 1.0,  2.0},
      { eul,  0.0}
   };

   for (const auto& z: numbers) {
      CHECK_EQ(fast_clog(  z), std::log(z), eps);
      CHECK_EQ(fast_clog_c(z), std::log(z), eps);
      CHECK_EQ(fast_clog_f(z), std::log(z), eps);
   }
   for (auto z: numbers) {
      z = -z;
      CHECK_EQ(fast_clog(  z), std::log(z), eps);
      CHECK_EQ(fast_clog_c(z), std::log(z), eps);
      CHECK_EQ(fast_clog_f(z), std::log(z), eps);
   }
}


int main()
{
   test_fast_clog();

   return errors;
}
