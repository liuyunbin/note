#!/bin/bash
#
# 此脚本用于安装 googletest
#

if which apt &> /dev/null; then
    # Ubuntu 20.04
    sudo apt install libgtest-dev -y
else
    # centos7
    tar xf googletest-release-1.10.0.tar.gz
    cd googletest-release-1.10.0
    mkdir -p build
    cd build
    cmake .. -DBUILD_GMOCK=OFF
    make
    sudo make install
    rm -rf ../../googletest-release-1.10.0
fi
