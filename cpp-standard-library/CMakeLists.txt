
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cpp-standard-library)

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

add_subdirectory(algorithm)
add_subdirectory(array)

