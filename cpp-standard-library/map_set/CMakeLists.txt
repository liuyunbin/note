
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    map_set-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    map_set-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME map_set-unittest
    COMMAND map_set-unittest
    )
