#!/bin/bash
#
# Author: Igor Lesik 2018
# 
# Usage: mkdir build && cd build && <path to source>/cmake [cmake arguments]
#

SRC_DIR=$(dirname ${BASH_SOURCE[0]})

CMAKE=cmake

echo "Calling $CMAKE $CMAKE_OPTS $@ $SRC_DIR"
echo ""

$CMAKE $CMAKE_OPTS $@ $SRC_DIR
