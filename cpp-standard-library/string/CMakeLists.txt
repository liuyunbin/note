
add_executable(
    cpp-standard-library-string-unittest
    string_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-string-unittest
    gtest
    gtest_main
    pthread
    )

