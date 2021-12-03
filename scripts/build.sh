#!/bin/bash

SCRIPT_DIR=`dirname "$(readlink -f "$0")"` 
BASE_DIR=`dirname "$SCRIPT_DIR"`

mkdir -p $BASE_DIR/build && cd $BASE_DIR/build
cmake ../ && make