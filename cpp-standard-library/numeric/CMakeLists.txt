
add_executable(
    cpp-standard-library-numeric-unittest
    accumulate/accumulate_unittest.cc
    adjacent_difference/adjacent_difference_unittest.cc
    inner_product/inner_product_unittest.cc
    iota/iota_unittest.cc
    partial_sum/partial_sum_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-numeric-unittest
    gtest
    gtest_main
    pthread
    )

