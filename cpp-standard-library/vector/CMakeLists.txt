
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    vector-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    vector-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME vector-unittest
    COMMAND vector-unittest
    )
