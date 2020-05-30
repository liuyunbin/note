
add_executable(
    map-unittest
    map/map_unittest.cc
    )

target_link_libraries(map-unittest gtest gtest_main pthread)  

