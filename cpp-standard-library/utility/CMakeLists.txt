
add_executable(
    cpp-standard-library-utility-unittest
    pair/pair_unittest.cc
    swap/swap_unittest.cc
    move/move_unittest.cc
    forward/forward_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-utility-unittest
    gtest
    gtest_main
    pthread
    )

