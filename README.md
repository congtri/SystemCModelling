# SystemC Modelling Repository

This repository is designed for SystemC modeling implementations. It includes SystemC version 3.0.0 as a sub-repository.

## Folder Structure

SystemCModelling
|
|-- doc                     # Documentation files
|-- libs                    # Libraries
|    |-- systemc-3.0.0      # SystemC library source code
|    |-- others...          # Additional libraries
|    |
|    |-- macm1build_libs    # Built libraries for MacOs M1
|        |-- systemc-3.0.0      # Built SystemC library for Mac M1
|
|-- models                  # Model implementations
|    |-- examples           # Example models
|    |-- Initiator2Receiver # Specific model: Initiator to Receiver
|    |-- others...          # Other models
|
|-- README.md               # This README file

## Building SystemC on Mac M1

To build SystemC for Mac M1, follow these steps. The commands are based on the official SystemC guidelines, tailored for the Mac M1 architecture and this specific folder structure:

1. **Open a terminal window.**
2. **Navigate to the `libs/systemc-3.0.0` directory** (or adjust the path as necessary based on your setup).
3. **Run the following commands:**

   ```bash
   export CXX=clang++

   cmake ../ -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=../../macm1built_libs/systemc-3.0.0 -DBUILD_SOURCE_DOCUMENTATION=ON

   make

   make install
   ```