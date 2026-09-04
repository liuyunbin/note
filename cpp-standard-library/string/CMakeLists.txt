
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    string-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    string-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME string-unittest
    COMMAND string-unittest
    )
