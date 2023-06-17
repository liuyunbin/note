
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

# 操作系统-僵尸进程
add_executable(10101 10101.cc)
add_executable(10102 10102.cc)
add_executable(10103 10103.cc)
add_executable(10104 10104.cc)
add_executable(10105 10105.cc)
add_executable(10106 10106.cc)
add_executable(10107 10107.cc)
add_executable(10108 10108.cc)

# 操作系统-孤儿进程
add_executable(10201 10201.cc)

# 操作系统-孤儿进程组
add_executable(10301 10301.cc)

# 操作系统- 信号
add_executable(10401 10401.cc)
add_executable(10402 10402.cc)
add_executable(10403 10403.cc)
add_executable(10404 10404.cc)
add_executable(10405 10405.cc)
add_executable(10406 10406.cc)
add_executable(10407 10407.cc)
add_executable(10408 10408.cc)
add_executable(10409 10409.cc)
add_executable(10410 10410.cc)
add_executable(10411 10411.cc)
add_executable(10412 10412.cc)
add_executable(10413 10413.cc)
add_executable(10414 10414.cc)
add_executable(10415 10415.cc)

# 操作系统-进程
add_executable(10501 10501.cc)
add_executable(10502 10502.cc)
add_executable(10503 10503.cc)
add_executable(10504 10504.cc)
add_executable(10505 10505.cc)

# 操作系统-进程组
add_executable(10601 10601.cc)
add_executable(10602 10602.cc)
add_executable(10603 10603.cc)
add_executable(10604 10604.cc)
add_executable(10605 10605.cc)
add_executable(10606 10606.cc)
add_executable(10607 10607.cc)
add_executable(10608 10608.cc)

# 会话
add_executable(10701 10701.cc)
add_executable(10702 10702.cc)
add_executable(10703 10703.cc)

# 计算机组成原理-整数-浮点数-字符
add_executable(20101 20101.cc)
add_executable(20102 20102.cc)
add_executable(20103 20103.cc)
add_executable(20104 20104.cc)
add_executable(20105 20105.cc)
add_executable(20106 20106.cc)
add_executable(20107 20107.cc)
add_executable(20108 20108.cc)
add_executable(20109 20109.cc)
add_executable(20110 20110.cc)

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
