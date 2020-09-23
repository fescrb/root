#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source $DIR/setup_environment.env 

echo "Building googletest"

cd $DIR/../thirdparty/googletest/

if [[ ! -d ./build ]]; then
    mkdir ./build
fi

cd ./build

C_FLAGS="-fPIC"
CXX_FLAGS="-std=c++17 $C_FLAGS"

cmake -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$CC -DCMAKE_C_FLAGS="$C_FLAGS" -DCMAKE_CXX_FLAGS="$CXX_FLAGS" -DCMAKE_INSTALL_PREFIX=$DIR/.. ..

if [ ! $? -eq 0 ]; then
    echo 'CMake failed. Quitting.'
    exit 1
fi

make

if [ ! $? -eq 0 ]; then
    echo 'Make failed. Quitting.'
    exit 1
fi

make install

echo "Building glfw"

cd $DIR/../thirdparty/glfw/

if [[ ! -d ./build ]]; then
    mkdir ./build
fi

cd ./build

C_FLAGS="-fPIC"
CXX_FLAGS="-std=c++17 $C_FLAGS"
LINK_FLAGS="-lvulkan"

cmake -DGLFW_VULKAN_STATIC=ON -DCMAKE_C_LINK_FLAGS=$LINK_FLAGS -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$CC -DCMAKE_C_FLAGS="$C_FLAGS" -DCMAKE_CXX_FLAGS="$CXX_FLAGS" -DCMAKE_INSTALL_PREFIX=$DIR/.. ..

if [ ! $? -eq 0 ]; then
    echo 'CMake failed. Quitting.'
    exit 1
fi

make

if [ ! $? -eq 0 ]; then
    echo 'Make failed. Quitting.'
    exit 1
fi

make install