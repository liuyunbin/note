
file(GLOB_RECURSE UNITTEST_FILE "*_unittest.cc")  # 递归

add_executable(
    type_traits-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    type_traits-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME type_traits-unittest
    COMMAND type_traits-unittest
    )
