add_library(fast_clog
  fast_clog.c
  fast_clog.f90
  )
target_include_directories(fast_clog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
