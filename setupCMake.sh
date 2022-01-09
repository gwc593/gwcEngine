#!/bin/bash

#clean up
rm -fr build
mkdir build

#execute cmake
cmake \
    -Bbuild \
    -DCMAKE_BUILD_TYPE=Release \

echo "CMake configured...."
echo "execute 'cmake --build ./build' to build project "
