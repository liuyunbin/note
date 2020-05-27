
add_executable(
    algorithm-unittest
    min_element/min_element_unittest.cc
    min/min_unittest.cc
    max_element/max_element_unittest.cc
    max/max_unittest.cc
    minmax_element/minmax_element_unittest.cc
    minmax/minmax_unittest.cc
    iter_swap/iter_swap_unittest.cc
    swap_ranges/swap_ranges_unittest.cc
    copy/copy_unittest.cc
    )

target_link_libraries(algorithm-unittest gtest gtest_main pthread)  

