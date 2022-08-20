add_executable(
    huge-number-unittest
    huge_number_unittest.cc
    huge_number.cc
    )

target_link_libraries(
    huge-number-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME huge-number-unittest
    COMMAND huge-number-unittest
    )
