#!/bin/bash

set -eux

cd third-party

mkdir -p lib
mkdir -p include

third_party=$(pwd)

if [ ! -d googletest ] ; then
    git clone git@github.com:google/googletest.git -b release-1.8.1
fi

cd googletest/googletest

mkdir -p build

cd build

cmake ..

make

cp libgtest.a libgtest_main.a ${third_party}/lib

cp -rf ../include/gtest ${third_party}/include
