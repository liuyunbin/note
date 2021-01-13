
file(GLOB_RECURSE UNITTEST_FILE "*_unittest.cc")  # 递归

add_executable(
    cpp-standard-library-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    cpp-standard-library-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME cpp-standard-library-unittest
    COMMAND cpp-standard-library-unittest
    )
