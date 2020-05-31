
add_executable(
    iterator-unittest
    back_insert_iterator/back_insert_iterator_unittest.cc
    front_insert_iterator/front_insert_iterator_unittest.cc
    )

target_link_libraries(iterator-unittest gtest gtest_main pthread)  

