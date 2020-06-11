
add_executable(
    cpp-standard-library-forward-list-unittest
    forward_list_unittest.cc)

target_link_libraries(
    cpp-standard-library-forward-list-unittest
    gtest
    gtest_main
    pthread
    )

