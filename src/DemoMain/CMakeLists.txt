# Set the module name
set(MODULE_NAME DemoMain)

# Collect source and header files
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Set the output directory for the executable
add_executable(${MODULE_NAME} ${SOURCES} ${HEADERS})

# Link against the QtCore dynamic library
target_link_libraries(${MODULE_NAME} PRIVATE QtCore)

# Specify include directories for the dependent library
target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Qt
)