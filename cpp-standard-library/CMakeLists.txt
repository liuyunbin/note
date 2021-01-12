
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cpp-standard-library) # 设置 二进制文件 的输出目录

# 添加 子目录
add_subdirectory(algorithm)
add_subdirectory(array)
add_subdirectory(cctype)
add_subdirectory(cstring)
add_subdirectory(deque)
add_subdirectory(forward_list)
add_subdirectory(iterator)
add_subdirectory(list)
add_subdirectory(map_set)
add_subdirectory(memory)
add_subdirectory(numeric)
add_subdirectory(queue)
add_subdirectory(stack)
add_subdirectory(string)
add_subdirectory(type_traits)
add_subdirectory(utility)
add_subdirectory(unordered_map_set)
add_subdirectory(vector)

