#!/bin/bash

set -ev


cmake -E make_directory "build"

cmake -E chdir "build" cmake ..

cmake --build "build"

cmake --build "build" --target test

