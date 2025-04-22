# Set the module name
set(MODULE_NAME QtCore)

# Collect source and header files
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB PRIVATE_HEADERS "./private/*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Header Files\\Private" FILES ${PRIVATE_HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Set the output directory for the executable
add_executable(${MODULE_NAME} ${SOURCES} ${HEADERS} ${PRIVATE_HEADERS})

# Specify include directories for header file lookup
target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# Add the subdirectory for the Qt modules
# This is where the Qt modules will be located
# add_subdirectory(private)