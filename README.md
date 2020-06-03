# Fast implementation of complex logarithms

Average run-time with clang++ 11 and `-Ofast -ffast-math` on an i7-5600U:

| Function                          | run-time in ms |
|-----------------------------------|----------------|
| `std::log(std::complex<double>&)` | 5.75e-05       |
| `fast_clog` (C++)                 | 4.11e-05       |
| `fast_clog` (C)                   | 4.33e-05       |


License: CC0
