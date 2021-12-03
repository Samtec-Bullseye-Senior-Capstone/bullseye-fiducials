#!/bin/bash

SCRIPT_DIR=`dirname "$(readlink -f "$0")"` 
BASE_DIR=`dirname "$SCRIPT_DIR"`

rm -rf $BASE_DIR/build && $SCRIPT_DIR/build.sh
cp $BASE_DIR/build/bullseye-fiducials /bin/bullseye-fiducials
