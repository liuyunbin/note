
add_executable(
    getopt-test
    getopt_test.cc
    getopt.cc
    )

target_link_libraries(
    getopt-test
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME getopt-test
    COMMAND getopt-test
    )
