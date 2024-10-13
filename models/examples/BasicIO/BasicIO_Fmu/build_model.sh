#!/bin/bash

PROJECT_NAME="BasicIO_Fmu"

echo "============================================================"
echo "Starting Build Process"
echo "============================================================"

# Cleanup previous build and create a new build directory
rm -rf build && mkdir build
cd build

# Stop script execution if any command fails
set -e

# Setup trap for cleanup on exit
trap 'echo "Script terminated"; exit' ERR

echo "Running CMake..."
cmake ../ || { echo "Error: CMake configuration failed"; exit 1; }

echo "Building project..."
# You can parameterize the number of jobs by adding a variable or argument
JOBS=${JOBS:-4} # Default to 4 if not set
cmake --build . -- -j"$JOBS" || { echo "Error: Build failed"; exit 1; }

echo "Installing project..."
cmake --install . || { echo "Error: Installation failed"; exit 1; }

echo "Project built and installed successfully!"

echo "============================================================"
echo "Creating ${PROJECT_NAME} FMU"
echo "============================================================"
# Define the current directory and FMU directory
CURRENT_DIR=$(pwd)
FMU_DIR="$CURRENT_DIR/${PROJECT_NAME}_Fmu"

# Create the FMU folder structure
mkdir -p "$FMU_DIR/sources"
mkdir -p "$FMU_DIR/binaries/darwin64"

echo "FMU structure for '$FMU_DIR' created successfully."

# Copy model description and built model to the FMU directory
cp "../modelDescription.xml" "${FMU_DIR}" || { echo "Error: Failed to copy modelDescription.xml"; exit 1; }

cp "result/${PROJECT_NAME}.dylib" "${FMU_DIR}/binaries/darwin64" || { echo "Error: Failed to copy built model"; exit 1; }

# Zip the FMU directory into a .fmu file
cd "$FMU_DIR"
zip -r "../${PROJECT_NAME}.fmu" * || { echo "Error: Failed to create .fmu file"; exit 1; }

echo "FMU created successfully: ${PROJECT_NAME}.fmu"
