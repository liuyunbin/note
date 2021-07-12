#!/bin/bash

set -eux

INSTALL_DIR=$(pwd)
GOOGLETEST=googletest-release-1.10.0

cd third-party/googletest

tar xvf ${GOOGLETEST}.tar.gz

mv ${GOOGLETEST} googletest

cd googletest

cmake .. -DBUILD_GMOCK=OFF -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}

make

make install

