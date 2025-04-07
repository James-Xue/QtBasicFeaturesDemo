# Set the minimum required version of CMake
# to 3.10, but allow up to 4.0 for future compatibility.
# This ensures that the project can be built with a wide range of CMake versions.
cmake_minimum_required(VERSION 3.10...4.0)

# Set the project name
project(Demo)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)

# Include directories
include_directories(src/Demo)

# Collect source and header files
file(GLOB SOURCES "src/Demo/*.cpp")
file(GLOB HEADERS "src/Demo/*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Set the output directory for the executable
add_executable(Demo ${SOURCES} ${HEADERS})
