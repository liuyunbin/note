
add_executable(
    cpp-standard-library-array-unittest
    array_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-array-unittest
    gtest
    gtest_main
    pthread
    )

