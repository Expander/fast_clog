add_library(fast_clog
  clog.f90
  fast_clog.c
  fast_clog.c99
  fast_clog.f90
  )
target_include_directories(fast_clog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
