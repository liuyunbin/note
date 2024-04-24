
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    list-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    list-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME list-unittest
    COMMAND list-unittest
    )
