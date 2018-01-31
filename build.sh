#!/bin/bash

SUFFIX=""
if [ $# -eq 1 ]; then
    SUFFIX="-$1"
fi

CONAN_DIR="conan$SUFFIX"
BUILD_DIR="build$SUFFIX"
export CONAN_USER_HOME=$PWD/$CONAN_DIR

if [ ! -d "$CONAN_DIR" ]; then
  mkdir $CONAN_DIR
  conan remote add conan-community https://api.bintray.com/conan/conan-community/conan
  conan remote add bernddoser https://api.bintray.com/conan/bernddoser/conan --insert
fi

rm -fr $BUILD_DIR
mkdir $BUILD_DIR
cd $BUILD_DIR

conan install .. --build=missing -s compiler.libcxx=libstdc++11
cmake ..
make 2>&1 |tee make.out