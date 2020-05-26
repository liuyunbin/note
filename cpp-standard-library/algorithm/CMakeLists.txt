
add_executable(
    algorithm-unittest
    min_element/min_element_unittest.cc
    )

target_link_libraries(algorithm-unittest gtest gtest_main pthread)  

