#!/bin/bash

# Function to create FMU folder structure
create_fmu_structure() {
    fmu_name="$1"
    
    # Create the main FMU folder
    mkdir -p "$fmu_name"

    # Create the resources directory
    mkdir -p "$fmu_name/resources"

    # Create the binary files directory
    mkdir -p "$fmu_name/binary_files"

    echo "FMU structure for '$fmu_name' created successfully."
}

PROJECT_NAME="BasicIO"

echo "============================================================"
echo "Starting Build Process"
echo "============================================================"

rm -rf build && mkdir build
cd build

# Stop script execution if any command fails
set -e

echo "Running CMake..."
cmake ../ || { echo "Error: CMake configuration failed"; exit 1; }

echo "Building project..."
cmake --build . -- -j4 || { echo "Error: Build failed"; exit 1; }

echo "Installing project..."
cmake --install . || { echo "Error: Installation failed"; exit 1; }

echo "Project built and installed successfully!"

# Define the current directory and FMU directory
CURRENT_DIR=$(pwd)
FMU_DIR="$CURRENT_DIR/${PROJECT_NAME}_Fmu"
create_fmu_structure "${FMU_DIR}"

# Copy model description and built model to the FMU directory
echo "Copying modelDescription.xml to '$FMU_DIR'..."
cp ../modelDescription.xml "${FMU_DIR}" || { echo "Error: Failed to copy modelDescription.xml"; exit 1; }

echo "Copying built model to '$FMU_DIR/binary_files'..."
# Assuming the built model file is located in the build directory, replace <built_model_name> with the actual filename
cp result/BasicIO.dylib "${FMU_DIR}/binary_files/" || { echo "Error: Failed to copy built model"; exit 1; }

echo "FMU structure updated with model description and built model."

# Zip the FMU directory into a .fmu file
cd "$CURRENT_DIR"
zip -r "${PROJECT_NAME}.fmu" "${PROJECT_NAME}_Fmu" || { echo "Error: Failed to create .fmu file"; exit 1; }

echo "FMU created successfully: ${PROJECT_NAME}.fmu"