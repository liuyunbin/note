#!/bin/bash

set -eux

INSTALL_DIR=$(pwd)
GOOGLETEST=googletest-release-1.10.0

cd third-party/googletest

rm -rf googletest

tar xvf ${GOOGLETEST}.tar.gz

mv ${GOOGLETEST} googletest

cd googletest

mkdir build

cd build

cmake .. -DBUILD_GMOCK=OFF -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}

make

make install

