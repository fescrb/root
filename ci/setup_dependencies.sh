#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

source $DIR/setup_environment.env 

function build_submodule {
    # $1 - path
    # $2 - C_FLAGS
    # $3 - CXX_FLAGS 
    # $4 - C_LINK_FLAGS
    # $5 - CXX_LINK_FLAGS
    # $6 - CMake options
    # CXX_FLAGS will include CFLAGS


    cd $1

    if [[ ! -d ./build ]]; then
        mkdir ./build
    fi

    cd ./build

    cmake $6 -DCMAKE_CXX_COMPILER=$CXX -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=$CC -DCMAKE_C_FLAGS="$2" -DCMAKE_CXX_FLAGS="$2 $3" -DCMAKE_CXX_LINK_FLAGS="$4 $5" -DCMAKE_C_LINK_FLAGS="$4" -DCMAKE_INSTALL_PREFIX=$DIR/.. ..

    if [ ! $? -eq 0 ]; then
        echo 'CMake failed.'
        return 1
    fi

    make

    if [ ! $? -eq 0 ]; then
        echo 'Make failed.'
        return 1
    fi

    make install

    return 0
}

echo "Building googletest"

build_submodule $DIR/../thirdparty/googletest/ "-fPIC" "-std=c++17" "" ""

if [ ! $? -eq 0 ]; then
    echo 'Failed to build googletest.'
    exit 1
fi

echo "Building glfw"

build_submodule $DIR/../thirdparty/glfw/ "-fPIC" "-std=c++17" "-lvulkan" "" "-DGLFW_VULKAN_STATIC=ON"

if [ ! $? -eq 0 ]; then
    echo 'Failed to build glfw.'
    exit 1
fi


echo "Building shaderc"

$DIR/../thirdparty/shaderc/utils/git-sync-deps

build_submodule $DIR/../thirdparty/shaderc/ "-fPIC" "-std=c++17" "" "" ""

if [ ! $? -eq 0 ]; then
    echo 'Failed to build shaderc.'
    exit 1
fi
