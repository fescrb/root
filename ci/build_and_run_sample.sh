#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PWD="$( pwd )"

source $DIR/setup_environment.env 

cd $DIR/../src/

gyp sample/universal_test.gyp


if [ ! $? -eq 0 ]; then
    echo 'GYP failed. Quitting.'
    exit 1
fi

make

if [ ! $? -eq 0 ]; then
    echo 'Make failed. Quitting.'
    exit 1
fi

./out/Default/universal_test