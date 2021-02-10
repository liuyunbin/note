
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
add_subdirectory(cctype)
add_subdirectory(cstring)
add_subdirectory(deque)
add_subdirectory(forward_list)
add_subdirectory(iterator)
add_subdirectory(list)
add_subdirectory(map_set)
add_subdirectory(memory)
add_subdirectory(numeric)
add_subdirectory(queue)
add_subdirectory(stack)
add_subdirectory(string)
add_subdirectory(type_traits)
add_subdirectory(unordered_map_set)

