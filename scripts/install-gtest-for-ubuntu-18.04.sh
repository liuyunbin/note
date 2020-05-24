#!/bin/bash

set -ev

sudo apt install libgtest-dev

cd /usr/src/gtest

sudo mkdir -p build

cd build

sudo cmake ..

sudo make

sudo make install

