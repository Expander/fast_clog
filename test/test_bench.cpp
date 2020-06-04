#include "fast_clog.h"
#include "fast_clog.hpp"
#include "stopwatch.hpp"
#include <iostream>
#include <complex>
#include <vector>


template <class T>
inline void do_not_optimize(const T& value)
{
   asm volatile("" : : "r,m"(value) : "memory");
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


using Sample_t = std::vector<std::complex<double> >;


Sample_t make_sample(double min, double max, std::size_t n)
{
   Sample_t sample;
   sample.reserve(n*n);

   for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t k = 0; k < n; ++k) {
         std::complex<double> z(
            min + i*(max - min)/n,
            min + k*(max - min)/n
            );
         sample.emplace_back(z);
      }
   }

   return sample;
}


template <class F>
double bench_fn(F f, const Sample_t& sample)
{
   bench::Stopwatch sw;
   sw.start();

   for (const auto& z: sample) {
      do_not_optimize(f(z));
   }

   sw.stop();

   return sw.get_time_in_milliseconds() / sample.size();
}


void test_bench()
{
   const auto sample = make_sample(-5.0, 5.0, 1000);

   const auto cpp = [](const std::complex<double>& z) { return fast_clog(z); };
   const auto c   = [](const std::complex<double>& z) { return fast_clog_c(z); };
   const auto f   = [](const std::complex<double>& z) { return fast_clog_f(z); };
   const auto stl = [](const std::complex<double>& z) { return std::log(z); };

   const auto time_cpp = bench_fn(cpp, sample);
   const auto time_c   = bench_fn(c  , sample);
   const auto time_f   = bench_fn(f  , sample);
   const auto time_stl = bench_fn(stl , sample);

   std::cout << "Average run-time for complex logarithm in ms:\n"
             << "STL       (C++    ): " << time_stl << '\n'
             << "fast_clog (C++    ): " << time_cpp << '\n'
             << "fast_clog (C      ): " << time_c << '\n'
             << "fast_clog (FORTRAN): " << time_f << '\n';
}


int main()
{
   test_bench();

   return 0;
}
