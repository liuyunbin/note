
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    queue-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    queue-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME queue-unittest
    COMMAND queue-unittest
    )
