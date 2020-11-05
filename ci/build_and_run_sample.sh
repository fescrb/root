#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PWD="$( pwd )"

$DIR/setup_dependencies.sh

if [ ! $? -eq 0 ]; then
    echo 'Failed to set up dependencies. Quitting.'
    exit 1
fi

source $DIR/setup_environment.env 

if [ ! -d $DIR/../build ]; then
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

SAMPLE_BUILD_DIR=$DIR/../src/sample/simple_window_app/build

if [ -d $SAMPLE_BUILD_DIR ]; then
    rm -rf $SAMPLE_BUILD_DIR 
fi

mkdir $SAMPLE_BUILD_DIR
cd $SAMPLE_BUILD_DIR

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