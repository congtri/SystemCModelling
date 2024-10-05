cmake_minimum_required(VERSION 3.10)
project(SystemC_Transmitter_Receiver)

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
    main.cpp         # Your main program source file
)

# Create the executable
add_executable(SystemC_Transmitter_Receiver ${SOURCES})

# Include SystemC headers
target_include_directories(SystemC_Transmitter_Receiver PRIVATE ../../../libs/macm1built_libs/systemc-3.0.0/include)

# Link SystemC library (dylib for Mac, adjust for Linux if needed)
if(APPLE)
    target_link_libraries(SystemC_Transmitter_Receiver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/macm1built_libs/systemc-3.0.0/lib/libsystemc.dylib)
    
    # Set RPATH for macOS to find the SystemC library at runtime
    set_target_properties(SystemC_Transmitter_Receiver PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "@loader_path/../../../libs/macm1built_libs/systemc-3.0.0/lib"
    )
else()
    target_link_libraries(SystemC_Transmitter_Receiver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}../../../libs/macm1built_libs/systemc-3.0.0/lib/libsystemc.so)
endif()

# Specify the installation directory
install(TARGETS SystemC_Transmitter_Receiver DESTINATION ${CMAKE_BINARY_DIR}/result)

