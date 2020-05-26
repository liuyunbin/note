
add_executable(
    numeric-unittest
    accumulate/accumulate_unittest.cc
    )

target_link_libraries(numeric-unittest gtest gtest_main pthread)  

