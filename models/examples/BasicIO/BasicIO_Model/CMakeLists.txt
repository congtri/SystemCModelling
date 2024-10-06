cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "BasicIO")
set(SYSTEMC_LIB_PATH "../../../../libs/macm1built_libs/systemc-3.0.0")

project(${PROJECT_NAME})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Print the current source and build directories
message(STATUS "Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Current build directory: ${CMAKE_CURRENT_BINARY_DIR}")

# Detect platform and set the correct compiler if on Mac M1
if(APPLE)
    message(STATUS "Building on macOS")
else()
    message(STATUS "Building on non-macOS platform")
endif()

# Set the source files
set(SOURCES
    BasicIO.cpp         # Your library source file
)

# Create the dynamic library
add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Set the output name and prefix
set_target_properties(${PROJECT_NAME} PROPERTIES 
    OUTPUT_NAME ${PROJECT_NAME}  # Sets the name to the same with project name
    PREFIX ""  # Removes the "lib" prefix
)

# Include SystemC headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SYSTEMC_LIB_PATH}/include)

# Link SystemC library (dylib for Mac, adjust for Linux if needed)
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${SYSTEMC_LIB_PATH}/lib/libsystemc.dylib)
    
    # Set RPATH for macOS to find the SystemC library at runtime
    set_target_properties(${PROJECT_NAME} PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@loader_path/${SYSTEMC_LIB_PATH}/lib"
    )
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${SYSTEMC_LIB_PATH}/lib/libsystemc.so)
endif()

# Specify the installation directory
message(STATUS "Installation directory: ${CMAKE_BINARY_DIR}/result")
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/result)