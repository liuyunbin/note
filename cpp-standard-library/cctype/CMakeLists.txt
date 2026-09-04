
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    cctype-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    cctype-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME cctype-unittest
    COMMAND cctype-unittest
    )
