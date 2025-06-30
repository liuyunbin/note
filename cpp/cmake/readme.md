
## 使用流程
```
$                                   # 1. 在指定目录下写 CMakeLists.txt，文件名区分大小写
$ mkdir -p build && cd build        # 2. 创建并切换到构建目录
$ cmake -DCMAKE_INSTALL_PREFIX=/usr # 3. 设置安装前缀，生成 Makefile
$ make                              # 4. 编译
$ make test                         # 5. 测试（可选）
$ make install                      # 6. 安装（可选）
```

## CMake 常用命令, 命令不区分大小写
```
message(STATUS      "message to display")   # 向用户输出提示信息
message(FATAL_ERROR "message to display")   # 向用户输出错误信息，构建直接停止

add_executable(executable-name source.cc)           # 构建二进制文件
target_link_libraries(executable-name library-name) # 对文件添加需要链接的库文件
add_library(library-name SHARED source.cc)          # 构建动态库
add_library(library-name STATIC source.cc)          # 构建静态库

set_target_properties(library-name-shared PROPERTIES VERSION 1.2  SOVERSION 1) # 设置动态库的版本

add_library(library-name-shared SHARED source.cc)                              # 同时构建动态库和静态库
add_library(library-name-static STATIC source.cc)
set_target_properties(library-name-shared PROPERTIES OUTPUT_NAME library-name) # 设置静态库文件的输出名字
set_target_properties(library-name-static PROPERTIES OUTPUT_NAME library-name) # 设置动态库文件的输出名字

file(GLOB HEADERS HEATERS "*.h") # 将当前目录下的所有头文件存入变量
file(GLOB_RECURSE HEADERS "*.h") # 将当前目录下的所有头文件存入变量 (包括子目录)

install(TARGETS format_iostream     # 安装目标文件: 二进制文件 和 库文件
        RUNTIME DESTINATION bin     # 设置二进制文件的安装目录
        LIBRARY DESTINATION lib     # 设置动态库的安装目录
        ARCHIVE DESTINATION lib)    # 设置静态库的安装目录

install(FILES format_iostream.cc    # 安装普通文件
       DESTINATION src)             # 设置安装目录

install(PROGRAMS ../../build.sh     # 安装的非目标文件的可执行文件
       DESTINATION script)          # 设置安装目录

install(DIRECTORY linux-game        # 安装此目录
       DESTINATION src)             # 设置安装目录

install(DIRECTORY linux-game/       # 安装此目录下的所有文件
       DESTINATION src)             # 设置安装目录

enable_testing()                        # 激活测试命令
add_test(test-name executable-name arg) # 添加测试程序

add_custom_target(doc COMMAND doxygen doc/Doxyfile  # 添加命令 make doc
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})              # 设置工作目录
```

### CMake 常用变量, 变量区分大小写
```
CMAKE_PROJECT_NAME   # 项目名称
CMKAE_SOURCE_DIR     # 项目的源目录
CMKAE_BINARY_DIR     # 项目的构建目录
CMAKE_INSTALL_PREFIX # 安装目录前缀
CMAKE_CXX_FLAGS      # C++ 编译选项
```

