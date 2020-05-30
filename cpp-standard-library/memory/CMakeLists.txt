
add_executable(
    memory-unittest
    allocator/allocator_unittest.cc
    )

target_link_libraries(memory-unittest gtest gtest_main pthread)  

