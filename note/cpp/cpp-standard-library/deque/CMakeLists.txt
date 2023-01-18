
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    deque-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    deque-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME deque-unittest
    COMMAND deque-unittest
    )
