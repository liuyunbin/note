
add_executable(
    iterator-unittest
    back_insert_iterator/back_insert_iterator_unittest.cc
    front_insert_iterator/front_insert_iterator_unittest.cc
    insert_iterator/insert_iterator_unittest.cc
    move_iterator/move_iterator_unittest.cc
    reverse_iterator/reverse_iterator_unittest.cc
    istream_iterator/istream_iterator_unittest.cc
    ostream_iterator/ostream_iterator_unittest.cc
    advance/advance_unittest.cc
    distance/distance_unittest.cc
    next/next_unittest.cc
    )

target_link_libraries(iterator-unittest gtest gtest_main pthread)  

