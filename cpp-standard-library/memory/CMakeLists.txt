
add_executable(
    cpp-standard-library-memory-unittest
    allocator/allocator_unittest.cc
    shared_ptr/shared_ptr_unittest.cc
    unique_ptr/unique_ptr_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-memory-unittest
    gtest
    gtest_main
    pthread
    )

