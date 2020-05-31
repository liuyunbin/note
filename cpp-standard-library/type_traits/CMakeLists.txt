
add_executable(
    type-traits-unittest
    is_void/is_void_unittest.cc
    )

target_link_libraries(type-traits-unittest gtest gtest_main pthread)  

