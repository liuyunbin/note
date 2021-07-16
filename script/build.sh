#!/bin/bash

set -eux

mkdir -p build

cd build

cmake .. \
         -DEVENT__DISABLE_OPENSSL=ON \
         -DEVENT__LIBRARY_TYPE=STATIC \
         -DEVENT__DISABLE_SAMPLES=ON \
         -DEVENT__DISABLE_TESTS=ON \
         -DEVENT__DISABLE_BENCHMARK=ON

make

make test

