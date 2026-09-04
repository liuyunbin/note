
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    array-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    array-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME array-unittest
    COMMAND array-unittest
    )
