
cmake_minimum_required(VERSION 2.8) # 设置所需要的 CMake 的最小版本

project(liuyunbin-toys) # 项目名称

set(CXX_FLAGS
    -Wall
#    -Werror # 将所有警告转为错误
    -Wextra
    -Wno-unused-parameter
    -std=c++11
    )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}") # 设置 C++ 编译选项

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # 设置 静态库     的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # 设置 动态库     的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 设置 二进制文件 的输出目录

include_directories(${CMAKE_SOURCE_DIR}/include) # 设置头文件的搜索目录
   link_directories(${CMAKE_SOURCE_DIR}/lib)     # 设置库文件的搜索目录
   link_directories(${CMAKE_SOURCE_DIR}/lib64)   # 设置库文件的搜索目录

enable_testing() # 激活测试

#add_subdirectory(third-party)
add_subdirectory(src)

