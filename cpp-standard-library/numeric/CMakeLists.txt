
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    numeric-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    numeric-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME numeric-unittest
    COMMAND numeric-unittest
    )
