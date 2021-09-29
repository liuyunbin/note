#!/bin/bash
set -u          # 使用未初始化的变量报错
set -e          # 只要发生错误就退出
set -o pipefail # 只要管道发生错误就退出
set -E          # 即使意外退出, 也会执行 trap 命令

mkdir -p build

cd build

cmake .. \
         -DEVENT__DISABLE_OPENSSL=ON \
         -DEVENT__LIBRARY_TYPE=STATIC \
         -DEVENT__DISABLE_SAMPLES=ON \
         -DEVENT__DISABLE_TESTS=ON \
         -DEVENT__DISABLE_BENCHMARK=ON

make

make test

