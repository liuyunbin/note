#!/bin/bash
#
# 本程序用于安装常用命令
#

set -ev

if which apt &> /dev/null; then
    sudo apt install clang-format -y

    sudo apt install cmake -y

    sudo apt install g++ -y

    sudo apt install icdiff -y

    sudo apt install libgoogle-glog-dev -y

    sudo apt install libgtest-dev -y

    sudo apt install vim -y
else
    sudo yum install google-benchmark-devel
fi
