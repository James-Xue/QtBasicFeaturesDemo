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

# Debug postfix for debug builds
set_target_properties(${MODULE_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)

# Set the output directory for the executable
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin")
set(RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin")

# get_target_property(DEMO_BINARY_DIR ${MODULE_NAME} RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "Demo binary directory (CMAKE_BINARY_DIR): ${CMAKE_BINARY_DIR}")
message(STATUS "Demo binary directory (RUNTIME_OUTPUT_DIRECTORY): ${RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "Demo binary directory (Debug): ${RUNTIME_OUTPUT_DIRECTORY_DEBUG}")
message(STATUS "Demo binary directory (Release): ${RUNTIME_OUTPUT_DIRECTORY_RELEASE}")

# set(QTCORE_DLL $<TARGET_FILE:${MODULE_NAME}>)

# Copy the .exe and .pdb files to the output directory
add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:${MODULE_NAME}> # Copy the .exe file
        ${RUNTIME_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_PDB_FILE:${MODULE_NAME}> # Copy the .pdb file (if it exists)
        ${RUNTIME_OUTPUT_DIRECTORY}
    COMMENT "Copying ${MODULE_NAME}'s .exe and .pdb files to ${RUNTIME_OUTPUT_DIRECTORY}"
)

# Set the working directory and command for debugging in Visual Studio
set_target_properties(${MODULE_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${RUNTIME_OUTPUT_DIRECTORY}"
    VS_DEBUGGER_COMMAND "${RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME}_d.exe"
)

# This is necessary for the executable to run correctly
# as it depends on the QtCore library.
# The copy command is executed after the build process
# add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#         $<TARGET_FILE:QtCore>
#         ${DEMO_BINARY_DIR}
#     COMMENT "Copying QtCore DLL to Demo output directory"
# )
