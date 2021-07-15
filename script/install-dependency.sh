#!/bin/bash

set -ev

sudo apt install cmake -y

sudo apt install libreadline-dev -y

sudo apt install libncurses5-dev libncursesw5-dev -y

sudo apt install libevent-dev -y

sudo apt install libgoogle-glog-dev -y

sudo apt install libprotobuf-dev -y

sudo apt install protobuf-compiler -y

#./third-party/googletest/install-googletest.sh

./third-party/openssl/install-openssl.sh

#./third-party/libevent/install-libevent.sh
