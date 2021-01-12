
add_executable(
    memory-unittest
    allocator/allocator_unittest.cc
    shared_ptr/shared_ptr_unittest.cc
    unique_ptr/unique_ptr_unittest.cc
    )

target_link_libraries(
    memory-unittest
    gtest
    gtest_main
    pthread
    )

