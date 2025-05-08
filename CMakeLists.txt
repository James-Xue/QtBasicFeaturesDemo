# Set the minimum required version of CMake
# to 3.10, but allow up to 4.0 for future compatibility.
# This ensures that the project can be built with a wide range of CMake versions.
cmake_minimum_required(VERSION 3.10...4.0)

# Set the project name
project(BioSense)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile options for all targets
# This will ensure that all targets in the project
# will use the same compile options, making it easier
# to maintain consistency across the project

if (MSVC)
    # Enable additional warnings for MSVC
    add_compile_options(
        /W4 # Enable level 4 warnings
        /Zc:__cplusplus # Enable C++ standard version
        /permissive- # Enable strict standard compliance
    )
endif()

if(MSVC)
    add_compile_options(
        -MP # Enable multi-threaded precompiled headers
        -INCREMENTAL # Enable incremental linking    
    )
endif()

# Define UNICODE and _UNICODE for all targets
add_compile_definitions(UNICODE _UNICODE)

# Add the subdirectory for the main demo application
# This is where the main application code will be located
# This will allow us to build the main application separately
# from the other components of the project
add_subdirectory(src)
