# Set the module name
set(MODULE_NAME BioSenseGui)

# Find the Qt6 package
# This will find the Qt6 package and all its components
# that are required for the project. The components are specified
# in the find_package command, and can be modified as needed.
set(Qt6_DIR "../../lib//Qt-6.9.0/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    Charts
    Quick
    Qml
    REQUIRED
)

# Define the .qrc resource files
set(Gui_RESOURCES "UI/Resources.qrc")

# Add the .qrc file to the build
qt_add_resources(Gui_QRC_SRCS ${Gui_RESOURCES})

# Collect source and header files
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Collect all resource files
SET(BioSenseGui_SRCS
    ${Gui_QRC_SRCS}
    ${SOURCES}
    ${HEADERS}
)

# Set the output directory for the executable
add_executable(${MODULE_NAME} ${BioSenseGui_SRCS})

# Include the generated resource files in the target
# target_sources(${MODULE_NAME} PRIVATE ${RESOURCE_SOURCES})

# Link against the Qt6Widgets library
target_link_libraries(${MODULE_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Charts
    Qt6::Widgets
    Qt6::Gui
    Qt6::Quick
    Qt6::Qml
)

# Specify include directories for the dependent library
target_include_directories(${MODULE_NAME} PRIVATE
    # ${CMAKE_SOURCE_DIR}/src/Qt
)

# Set the output directory for the executable
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Debug postfix for debug builds
set_target_properties(${MODULE_NAME} PROPERTIES DEBUG_POSTFIX "_d")

# set(CMAKE_AUTOMOC TRUE)
# set(CMAKE_AUTOUIC TRUE)
# set(CMAKE_AUTORCC TRUE)

# message(STATUS "Demo binary directory (CMAKE_BINARY_DIR): ${CMAKE_BINARY_DIR}")
# message(STATUS "Demo binary directory (RUNTIME_OUTPUT_DIRECTORY): ${RUNTIME_OUTPUT_DIRECTORY}")

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
