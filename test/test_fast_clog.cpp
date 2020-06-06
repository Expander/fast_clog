#include "clog.h"
#include "fast_clog.h"
#include "fast_clog.hpp"
#include <cstdio>
#include <limits>
#include <complex>


unsigned errors = 0;


bool is_equal(double a, double b, double eps)
{
   return std::abs(a - b) <= eps;
}


#define CHECK_EQ(lhs,rhs,eps)                                           \
   do {                                                                 \
      const auto rl = std::real(lhs), il = std::imag(lhs);              \
      const auto rr = std::real(rhs), ir = std::imag(rhs);              \
      if (!is_equal(rl, rr, eps)) {                                     \
         printf("FAILED test in real part in line %d: "                 \
                "lhs (%.16f) != rhs (%.16f)\n",                         \
                __LINE__, rl, rr);                                      \
         errors++;                                                      \
      }                                                                 \
      if (!is_equal(il, ir, eps)) {                                     \
         printf("FAILED test in imag part in line %d: "                 \
                "lhs (%.16f) != rhs (%.16f)\n",                         \
                __LINE__, il, ir);                                      \
         errors++;                                                      \
      }                                                                 \
   } while (0)


std::complex<double> clog_f(const std::complex<double>& z)
{
   const double re = std::real(z), im = std::imag(z);
   double out_re, out_im;
   clog_(&re, &im, &out_re, &out_im);
   return { out_re, out_im };
}


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
      CHECK_EQ(fast_clog_f(z), clog_f(z)  , eps);
   }
   for (auto z: numbers) {
      z = -z;
      CHECK_EQ(fast_clog(  z), std::log(z), eps);
      CHECK_EQ(fast_clog_c(z), std::log(z), eps);
      CHECK_EQ(fast_clog_f(z), clog_f(z)  , eps);
   }
}


int main()
{
   test_fast_clog();

   return errors;
}
