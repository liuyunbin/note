
add_executable(
    cpp-standard-library-stack-unittest
    stack_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-stack-unittest
    gtest
    gtest_main
    pthread
    )

