
add_subdirectory(cpp)

add_executable(lsh lsh.cc)
target_link_libraries(lsh readline)

