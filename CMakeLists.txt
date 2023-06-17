
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
add_executable(0101 bash/0101.cc)
add_executable(0102 bash/0102.cc)
add_executable(0103 bash/0103.cc)
add_executable(0104 bash/0104.cc)
add_executable(0105 bash/0105.cc)
add_executable(0106 bash/0106.cc)
add_executable(0107 bash/0107.cc)
add_executable(0108 bash/0108.cc)

# 操作系统-孤儿进程
add_executable(0201 bash/0201.cc)

# 操作系统-孤儿进程组
add_executable(0301 bash/0301.cc)

# 操作系统- 信号
add_executable(0401 bash/0401.cc)
add_executable(0402 bash/0402.cc)
add_executable(0403 bash/0403.cc)
add_executable(0404 bash/0404.cc)
add_executable(0405 bash/0405.cc)
add_executable(0406 bash/0406.cc)
add_executable(0407 bash/0407.cc)
add_executable(0408 bash/0408.cc)
add_executable(0409 bash/0409.cc)
add_executable(0410 bash/0410.cc)
add_executable(0411 bash/0411.cc)
add_executable(0412 bash/0412.cc)
add_executable(0413 bash/0413.cc)
add_executable(0414 bash/0414.cc)
add_executable(0415 bash/0415.cc)

# 操作系统-进程
add_executable(0501 bash/0501.cc)
add_executable(0502 bash/0502.cc)
add_executable(0503 bash/0503.cc)
add_executable(0504 bash/0504.cc)
add_executable(0505 bash/0505.cc)

# 操作系统-进程组
add_executable(0601 bash/0601.cc)
add_executable(0602 bash/0602.cc)
add_executable(0603 bash/0603.cc)
add_executable(0604 bash/0604.cc)
add_executable(0605 bash/0605.cc)
add_executable(0606 bash/0606.cc)
add_executable(0607 bash/0607.cc)
add_executable(0608 bash/0608.cc)

# 会话
add_executable(0701 bash/0701.cc)
add_executable(0702 bash/0702.cc)
add_executable(0703 bash/0703.cc)

# 计算机组成原理-整数-浮点数-字符
add_executable(0801 bash/0801.cc)
add_executable(0802 bash/0802.cc)
add_executable(0803 bash/0803.cc)
add_executable(0804 bash/0804.cc)
add_executable(0805 bash/0805.cc)
add_executable(0806 bash/0806.cc)
add_executable(0807 bash/0807.cc)
add_executable(0808 bash/0808.cc)
add_executable(0809 bash/0809.cc)
add_executable(0810 bash/0810.cc)

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
