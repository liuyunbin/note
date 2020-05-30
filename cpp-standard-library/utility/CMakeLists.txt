
add_executable(
    utility-unittest
    pair/pair_unittest.cc
    )

target_link_libraries(utility-unittest gtest gtest_main pthread)  

