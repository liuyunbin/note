
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    algorithm-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    algorithm-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME algorithm-unittest
    COMMAND algorithm-unittest
    )
