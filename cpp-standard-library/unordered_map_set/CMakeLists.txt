
add_executable(
    cpp-standard-library-unordered-map-set-unittest
    unordered_map/unordered_map_unittest.cc
    unordered_multimap/unordered_multimap_unittest.cc
    unordered_set/unordered_set_unittest.cc
    unordered_multiset/unordered_multiset_unittest.cc
    )

target_link_libraries(
    cpp-standard-library-unordered-map-set-unittest
    gtest
    gtest_main
    pthread
    )

