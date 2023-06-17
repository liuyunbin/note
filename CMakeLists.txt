
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

# 信号
#add_executable(00101 src/001/01.cc)
#add_executable(00102 src/001/02.cc)
#add_executable(00103 src/001/03.cc)
#add_executable(00104 src/001/04.cc)
#add_executable(00105 src/001/05.cc)
#add_executable(00106 src/001/06.cc)
#add_executable(00107 src/001/07.cc)
#add_executable(00108 src/001/08.cc)
#add_executable(00109 src/001/09.cc)
#add_executable(00110 src/001/10.cc)
#add_executable(00111 src/001/11.cc)
#add_executable(00112 src/001/12.cc)
#add_executable(00113 src/001/13.cc)
#add_executable(00114 src/001/14.cc)
#add_executable(00115 src/001/15.cc)
#
## 进程
#add_executable(00201 src/002/01.cc)
#add_executable(00202 src/002/02.cc)
#add_executable(00203 src/002/03.cc)
#add_executable(00204 src/002/04.cc)
#add_executable(00205 src/002/05.cc)
#
## 进程组
#add_executable(00301 src/003/01.cc)
#add_executable(00302 src/003/02.cc)
#add_executable(00303 src/003/03.cc)
#add_executable(00304 src/003/04.cc)
#add_executable(00305 src/003/05.cc)
#add_executable(00306 src/003/06.cc)
#add_executable(00307 src/003/07.cc)
#add_executable(00308 src/003/08.cc)
#
## 会话
#add_executable(00401 src/004/01.cc)
#add_executable(00402 src/004/02.cc)
#add_executable(00403 src/004/03.cc)
#
## 整数 浮点数 字符的存储
#add_executable(10101 src/101/01.cc)
#add_executable(10102 src/101/02.cc)
#add_executable(10103 src/101/03.cc)
#add_executable(10104 src/101/04.cc)
#add_executable(10105 src/101/05.cc)
#add_executable(10106 src/101/06.cc)
#add_executable(10107 src/101/07.cc)
#add_executable(10108 src/101/08.cc)
#add_executable(10109 src/101/09.cc)
#add_executable(10110 src/101/10.cc)

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
