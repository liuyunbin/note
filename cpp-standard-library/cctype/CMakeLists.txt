
add_executable(
    cctype-unittest
    islower/islower_unittest.cc
    )

target_link_libraries(cctype-unittest gtest gtest_main pthread)  

