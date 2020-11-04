#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PWD="$( pwd )"

source $DIR/setup_environment.env 

if [ ! -f $DIR/../build ]; then
    mkdir $DIR/../build
fi

cd $DIR/../build

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$DIR/.." ..

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

if [ ! -f $DIR/../src/sample/simple_window_app/build ]; then
    mkdir $DIR/../src/sample/simple_window_app/build 
fi

cd $DIR/../src/sample/simple_window_app/build 

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="$DIR/.." ..

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

$DIR/../bin/simple_window_app