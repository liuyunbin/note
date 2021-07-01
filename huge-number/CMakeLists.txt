
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/huge-number)

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
