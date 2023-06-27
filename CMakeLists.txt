
cmake_minimum_required(VERSION 3.2) # 设置所需要的 CMake 的最小版本

project(note) # 项目名称

set(CXX_FLAGS
    -Wall
    -Werror                # 将所有警告转为错误
    -Wextra
    -Wno-unused-parameter
    -std=c++11
    )

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}") # 设置 C++ 编译选项

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # 设置 静态库     的输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib) # 设置 动态库     的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 设置 二进制文件 的输出目录

#include_directories(${CMAKE_SOURCE_DIR}/include) # 设置头文件的搜索目录
#   link_directories(${CMAKE_SOURCE_DIR}/lib)     # 设置库文件的搜索目录
#   link_directories(${CMAKE_SOURCE_DIR}/lib64)   # 设置库文件的搜索目录

# 激活测试
enable_testing()

# 计算机操作系统-僵尸进程
add_executable(001-01 001-01.cc)
add_executable(001-02 001-02.cc)
add_executable(001-03 001-03.cc)
add_executable(001-04 001-04.cc)
add_executable(001-05 001-05.cc)
add_executable(001-06 001-06.cc)
add_executable(001-07 001-07.cc)
add_executable(001-08 001-08.cc)

## 计算机操作系统-孤儿进程
#add_executable(002-01 002-01.cc)
#
## 计算机操作系统-孤儿进程组
#add_executable(003-01 003-01.cc)
#
## 计算机操作系统-信号
#add_executable(004-01 004-01.cc)
#add_executable(004-02 004-02.cc)
#add_executable(004-03 004-03.cc)
#add_executable(004-04 004-04.cc)
#add_executable(004-05 004-05.cc)
#add_executable(004-06 004-06.cc)
#add_executable(004-07 004-07.cc)
#add_executable(004-08 004-08.cc)
#add_executable(004-09 004-09.cc)
#add_executable(004-10 004-10.cc)
#add_executable(004-11 004-11.cc)
#add_executable(004-12 004-12.cc)
#add_executable(004-13 004-13.cc)
#add_executable(004-14 004-14.cc)
#add_executable(004-15 004-15.cc)
#
## 计算机操作系统-进程
#add_executable(005-01 005-01.cc)
#add_executable(005-02 005-02.cc)
#add_executable(005-03 005-03.cc)
#add_executable(005-04 005-04.cc)
#add_executable(005-05 005-05.cc)
#
## 计算机操作系统-进程组
#add_executable(006-01 006-01.cc)
#add_executable(006-02 006-02.cc)
#add_executable(006-03 006-03.cc)
#add_executable(006-04 006-04.cc)
#add_executable(006-05 006-05.cc)
#add_executable(006-06 006-06.cc)
#add_executable(006-07 006-07.cc)
#add_executable(006-08 006-08.cc)
#
## 会话
#add_executable(007-01 007-01.cc)
#add_executable(007-02 007-02.cc)
#add_executable(007-03 007-03.cc)
#
## 计算机组成原理-整数-浮点数-字符
#add_executable(101-01 101-01.cc)
#add_executable(101-02 101-02.cc)
#add_executable(101-03 101-03.cc)
#add_executable(101-04 101-04.cc)
#add_executable(101-05 101-05.cc)
#add_executable(101-06 101-06.cc)
#add_executable(101-07 101-07.cc)
#add_executable(101-08 101-08.cc)
#add_executable(101-09 101-09.cc)
#add_executable(101-10 101-10.cc)
#
## 计算机语言-C++
#add_executable(302-01 302-01.cc)

###########################################################################

# add_executable(lsh lsh.cc)
# target_link_libraries(lsh readline)

#add_executable(
#    huge-number-unittest
#    huge_number_unittest.cc
#    huge_number.cc
#    )
#
#target_link_libraries(
#    huge-number-unittest
#    gtest
#    gtest_main
#    pthread
#    )
#
#add_test(
#    NAME huge-number-unittest
#    COMMAND huge-number-unittest
#    )
