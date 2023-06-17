
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
add_executable(0101 0101.cc)
add_executable(0102 0102.cc)
add_executable(0103 0103.cc)
add_executable(0104 0104.cc)
add_executable(0105 0105.cc)
add_executable(0106 0106.cc)
add_executable(0107 0107.cc)
add_executable(0108 0108.cc)

# 操作系统-孤儿进程
add_executable(0201 0201.cc)

# 操作系统-孤儿进程组
add_executable(0301 0301.cc)

# 操作系统- 信号
add_executable(0401 0401.cc)
add_executable(0402 0402.cc)
add_executable(0403 0403.cc)
add_executable(0404 0404.cc)
add_executable(0405 0405.cc)
add_executable(0406 0406.cc)
add_executable(0407 0407.cc)
add_executable(0408 0408.cc)
add_executable(0409 0409.cc)
add_executable(0410 0410.cc)
add_executable(0411 0411.cc)
add_executable(0412 0412.cc)
add_executable(0413 0413.cc)
add_executable(0414 0414.cc)
add_executable(0415 0415.cc)

# 操作系统-进程
add_executable(0501 0501.cc)
add_executable(0502 0502.cc)
add_executable(0503 0503.cc)
add_executable(0504 0504.cc)
add_executable(0505 0505.cc)

# 操作系统-进程组
add_executable(0601 0601.cc)
add_executable(0602 0602.cc)
add_executable(0603 0603.cc)
add_executable(0604 0604.cc)
add_executable(0605 0605.cc)
add_executable(0606 0606.cc)
add_executable(0607 0607.cc)
add_executable(0608 0608.cc)

# 会话
add_executable(0701 0701.cc)
add_executable(0702 0702.cc)
add_executable(0703 0703.cc)

# 计算机组成原理-整数-浮点数-字符
add_executable(0801 0801.cc)
add_executable(0802 0802.cc)
add_executable(0803 0803.cc)
add_executable(0804 0804.cc)
add_executable(0805 0805.cc)
add_executable(0806 0806.cc)
add_executable(0807 0807.cc)
add_executable(0808 0808.cc)
add_executable(0809 0809.cc)
add_executable(0810 0810.cc)

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
