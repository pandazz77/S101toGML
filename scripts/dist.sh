#!/bin/bash

# Build dist

rm -rf build
mkdir build
cd build
cmake .. -DBUILD_SHARED_LIBS=ON
cmake --build . -j 8 --config Release
cmake --install . --prefix dist