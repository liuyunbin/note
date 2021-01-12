
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/linux-commands) # 设置 二进制文件 的输出目录

add_subdirectory(bc)
add_subdirectory(cp)
add_subdirectory(ls)
add_subdirectory(more)
add_subdirectory(shell)

