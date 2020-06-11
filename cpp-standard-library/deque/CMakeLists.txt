
add_executable(
    cpp-standard-library-deque-unittest
    deque_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-deque-unittest
    gtest
    gtest_main
    pthread
    )

