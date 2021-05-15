
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    utility-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    utility-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME utility-unittest
    COMMAND utility-unittest
    )
