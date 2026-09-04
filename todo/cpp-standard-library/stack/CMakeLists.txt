
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    stack-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    stack-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME stack-unittest
    COMMAND stack-unittest
    )
