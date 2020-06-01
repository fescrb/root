#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PWD="$( pwd )"

$DIR/setup_dependencies.sh

source $DIR/setup_environment.env 

cd $DIR/../src

gyp build/unit_tests.gyp

make

./out/Default/unit_tests