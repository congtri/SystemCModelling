cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "BasicIO_Fmu")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adjust these paths to your SystemC and FMI installations
set(SYSTEMC_HOME "../../../../libs/macm1built_libs/systemc-3.0.0")  # Adjust this path
set(FMI_HOME ${CMAKE_CURRENT_SOURCE_DIR})  # Adjust this path
set(SYSTEMC_MODEL_DIR "../BasicIO_Model")

# Include directories
include_directories(
    ${SYSTEMC_HOME}/include
    ${SYSTEMC_MODEL_DIR}  # For BasicIO.hpp
)

# Link directories
link_directories(
    ${SYSTEMC_HOME}/lib
)

# Add your source files without main.cpp
add_library(${PROJECT_NAME} SHARED
    fmu_wrapper.cpp
    ${SYSTEMC_MODEL_DIR}/BasicIO.cpp  # Include your SystemC model source
)

# Set the library name prefix to empty string and suffix to .dylib
set_target_properties(${PROJECT_NAME} PROPERTIES 
    PREFIX ""
    SUFFIX ".dylib"
)

# Link against necessary libraries
target_link_libraries(${PROJECT_NAME}
    systemc
)

# Special flags for Mac M1
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch arm64")

# Specify the output directory for the library during build
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/result)

# Installation rules
message(STATUS "Installation directory: ${CMAKE_BINARY_DIR}/result")
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/result)
