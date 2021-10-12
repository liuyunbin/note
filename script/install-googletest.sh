#!/bin/bash
#
# 此脚本用于在 centos7 下安装 googletest
#
# Ubuntu 20.04 上可以直接使用 `sudo apt install libgtest-dev` 安装 googletest
#

tar xf googletest-release-1.10.0.tar.gz
cd googletest-release-1.10.0
mkdir -p build
cd build
cmake .. -DBUILD_GMOCK=OFF
make
sudo make install
rm -rf ../../googletest-release-1.10.0
