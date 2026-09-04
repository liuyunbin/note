
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    iterator-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    iterator-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME iterator-unittest
    COMMAND iterator-unittest
    )
