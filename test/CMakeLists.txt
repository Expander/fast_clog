add_executable(test_fast_clog test_fast_clog.cpp)
target_link_libraries(test_fast_clog fast_clog)
add_test(NAME test_fast_clog COMMAND test_fast_clog)

# add_executable(test_bench test_bench.cpp)
# target_link_libraries(test_bench fast_clog)
# add_test(NAME test_bench COMMAND test_bench)
