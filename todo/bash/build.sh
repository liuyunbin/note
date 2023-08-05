#!/bin/bash

set -ueo pipefail

mkdir -p build
cd build
cmake ..
make
# make test
cd ..
rm -r build

