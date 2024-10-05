#!/bin/bash

echo "Removing build folder..."
rm -rf build

echo "Creating build folder..."
mkdir build
cd build

echo "Running CMake..."
cmake ../

echo "Building project..."
cmake --build . -- -j4

echo "Installing project..."
cmake --install .