
add_executable(
    cpp-standard-library-vector-unittest
    vector_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-vector-unittest
    gtest
    gtest_main
    pthread
    )

