#!/bin/sh
[ ! -d build ] && (mkdir -p build && cd build && cmake ..)
cmake --build build --clean-first
