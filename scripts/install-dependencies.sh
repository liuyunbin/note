#!/bin/bash

set -ev

sudo apt install cmake -y

sudo apt install libreadline-dev -y

sudo apt install libncurses5-dev libncursesw5-dev -y

sudo apt install libevent-dev -y

./scripts/install-gtest-for-ubuntu-20.04.sh

