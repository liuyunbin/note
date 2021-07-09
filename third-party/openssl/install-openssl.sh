#!/bin/bash

set -eux

INSTALL_DIR=$(pwd)
OPENSSL=openssl-1.1.1j

cd third-party/openssl

tar xvf ${OPENSSL}.tar.gz

mv ${OPENSSL} openssl

cd openssl

./config --prefix=${INSTALL_DIR} no-tests no-shared
make
#make test
make install

