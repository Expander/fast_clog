# Fast implementation of complex logarithms

Real and complex logarithms frequently appear in high-energy physics
calculations. In numerical applications, these logarithms have to be
calculated hundreds to millions of times, depending on the considered
example. For this reason, a fast numerical evaluation is of high
importance, in particular in studies of models with a parameter space
with a large dimensionality.

The usual implementation of the complex logarithm in mathematical
libraries is of the form

    log(z) = log(|z|) + i*arg(z)

where `|z|` is the magnitude and `arg(z)` is the polar angle of the
complex number `z`. The evaluation of this expression requires the
calculation of a square root (sometimes implemented by calling the
`hypot()` function) and sometimes a small extra overhead when
calculating the polar angle with `arg(z)`.

The complex logarithm can be calculated in a more performant way by
writing it as

    log(z) = 0.5*log(re*re + im*im) + i*atan2(im, re)

where `re = Re(z)` and `im = Im(z)`. This expression avoids the
calculation of the square root and a potential overhead from the
`arg(z)` function. Note, however, that the more performant form is
restricted to complex numbers with `|z|^2 < inf`, while the slower
form is in principle valid for `|z| < inf`.

The following table compares the average run-time of the `std::log()`
function from the C++ STL with more performant implementations
contained in this package (compiler: clang++ 11, compiler flags:
`-Ofast -ffast-math`, CPU: i7-5600U):

| Function                                      | run-time in ms |
|-----------------------------------------------|----------------|
| `std::log(const std::complex<double>&)` (C++) | 5.6e-05        |
| `fast_clog` (C++)                             | 3.7e-05        |
| `fast_clog` (C)                               | 3.9e-05        |
|                                               |                |
| `log(double complex)` (FORTRAN)               | 6.0e-05        |
| `fast_clog` (FORTRAN)                         | 4.2e-05        |


License: CC0
