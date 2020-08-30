#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

function try_remove_tree {
    if [[ -d $1 ]]; then
        echo "Removing $1"
        rm -rf $1
    fi
}

# Try to remove gtest artifacts
try_remove_tree $DIR/../lib
try_remove_tree $DIR/../include/gmock
try_remove_tree $DIR/../include/gtest
try_remove_tree $DIR/../thirdparty/googletest/build

# Get rid of our own artifacts
find .. -type f | grep Makefile | grep -v thirdparty | xargs rm
find .. -type f | grep .mk | grep -v thirdparty | xargs rm