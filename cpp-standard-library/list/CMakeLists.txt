
add_executable(
    list-unittest
    list_unittest.cc
    )

target_link_libraries(
    list-unittest
    gtest
    gtest_main
    pthread
    )

