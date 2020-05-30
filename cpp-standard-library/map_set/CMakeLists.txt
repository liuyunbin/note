
add_executable(
    map-set-unittest
    map/map_unittest.cc
    multimap/multimap_unittest.cc
    set/set_unittest.cc
    multiset/multiset_unittest.cc
    )

target_link_libraries(map-set-unittest gtest gtest_main pthread)  

