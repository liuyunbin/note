
add_executable(
    vector-unittest
    vector_unittest.cc
    )

target_link_libraries(
    vector-unittest
    gtest
    gtest_main
    pthread
    )

