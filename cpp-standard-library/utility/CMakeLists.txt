
add_executable(
    utility-unittest
    pair/pair_unittest.cc
    swap/swap_unittest.cc
    move/move_unittest.cc
    )

target_link_libraries(utility-unittest gtest gtest_main pthread)  

