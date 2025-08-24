#!/bin/bash

# Name: build_release.sh
# Usage: ./build_release.sh

# Build type is fixed to Release
BUILD_TYPE=Release

# Create and enter build directory
mkdir -p build
cd build || exit 1

# Configure CMake
echo "Configuring CMake with build type: $BUILD_TYPE"
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build the project
echo "Building the project..."
cmake --build . -- -j$(nproc)

echo "Release build finished!"