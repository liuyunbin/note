
add_executable(
    cpp-standard-library-list-unittest
    list_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-list-unittest
    gtest
    gtest_main
    pthread
    )

