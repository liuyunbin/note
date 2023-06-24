
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    memory-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    memory-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME memory-unittest
    COMMAND memory-unittest
    )
