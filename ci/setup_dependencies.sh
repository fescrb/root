#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source $DIR/setup_environment.env 

cd $DIR/../thirdparty/googletest/

if [[ ! -d ./build ]]; then
    mkdir ./build
fi

cd ./build

FLAGS="-std=c++17 -fPIC"

cmake -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_C_COMPILER=$CC -DCMAKE_C_FLAGS="$FLAGS" -DCMAKE_CXX_FLAGS="$FLAGS" -DCMAKE_INSTALL_PREFIX=$DIR/.. ..

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