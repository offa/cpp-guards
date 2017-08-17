#!/bin/bash

set -ex

## Install GTest
export GTEST_VERSION=master
export GTEST=googletest-${GTEST_VERSION}

wget https://github.com/google/googletest/archive/${GTEST_VERSION}.tar.gz
tar -xzf *.tar.gz
cd ${GTEST}
mkdir build && cd build

if [[ "$CXX" == clang* ]]; then
    export CXXFLAGS="-stdlib=libc++"
fi

cmake ..

make -j4 && sudo make install
cd ../..

