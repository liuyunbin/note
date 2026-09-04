
file(GLOB UNITTEST_FILE "*_unittest.cc")

add_executable(
    forward_list-unittest
    ${UNITTEST_FILE}
    )

target_link_libraries(
    forward_list-unittest
    gtest
    gtest_main
    pthread
    )

add_test(
    NAME forward_list-unittest
    COMMAND forward_list-unittest
    )
