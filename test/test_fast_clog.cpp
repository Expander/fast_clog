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


void test_fast_clog()
{
   const double eps = std::numeric_limits<double>::epsilon();
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
      { 1.0,  2.0}
   };

   for (const auto& z: numbers) {
      CHECK_EQ(fast_clog_c( z), std::log( z), eps);
      CHECK_EQ(fast_clog_c(-z), std::log(-z), eps);
      CHECK_EQ(fast_clog(   z), std::log( z), eps);
      CHECK_EQ(fast_clog(  -z), std::log(-z), eps);
   }
}


int main()
{
   test_fast_clog();

   return errors;
}
