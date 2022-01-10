#!/bin/bash

#clean up
rm -fr build
mkdir build

#execute cmake
cmake \
    -Bbuild \
    -DCMAKE_BUILD_TYPE=Release \
#    -DGE_PLATFORM_LINUX=1

echo "CMake configured...."
echo "execute 'cmake --build ./build' to build project "
