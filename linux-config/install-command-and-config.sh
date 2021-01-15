#!/bin/bash

set -ev

sudo apt install clang-format -y

sudo apt install cmake -y

sudo apt install g++ -y

sudo apt install libevent-dev -y

sudo apt install libreadline-dev -y

sudo apt install libgoogle-glog-dev -y

sudo apt install libprotobuf-dev -y

sudo apt install protobuf-compiler -y

sudo apt install vim -y

cat vimrc >> ~/.vimrc

cat bashrc >> ~/.bashrc

