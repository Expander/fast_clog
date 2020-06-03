#pragma once

#include <cmath>
#include <complex>

template <typename T>
std::complex<T> fast_clog(const std::complex<T>& z) noexcept
{
   const T re = std::real(z);
   const T im = std::imag(z);

   return { 0.5*std::log(re*re + im*im), std::atan2(im, re) };
}
