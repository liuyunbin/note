
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    unordered_map_set-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    unordered_map_set-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME unordered_map_set-unittest
    COMMAND unordered_map_set-unittest
    )
