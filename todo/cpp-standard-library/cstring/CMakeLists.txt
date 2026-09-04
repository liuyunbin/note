
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    cstring-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    cstring-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME cstring-unittest
    COMMAND cstring-unittest
    )
