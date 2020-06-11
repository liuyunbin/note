
add_executable(
    forward-list-unittest
    forward_list_unittest.cc)

target_link_libraries(
    forward-list-unittest
    gtest
    gtest_main
    pthread
    )

