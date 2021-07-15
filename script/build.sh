#!/bin/bash

set -eux

mkdir -p build

cd build

cmake .. -DEVENT__DISABLE_OPENSSL=ON \
         -DEVENT__LIBRARY_TYPE=STATIC

make

