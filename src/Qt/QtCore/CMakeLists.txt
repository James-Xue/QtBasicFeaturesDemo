# Set the module name
set(MODULE_NAME QtCore)

# Collect source and header files
#file(GLOB SOURCES "*.cpp")
file(GLOB SOURCES
 "qstring.cpp"
 "qfile.cpp"
 "qassert.cpp"
 "qlogging.cpp"
 "qbytearray.cpp"
 "qarraydata.cpp"
 "qbytearraymatcher.cpp"
 "qdatastream.cpp"
 "qmetaobject.cpp"
 "qmetatype.cpp"
 "qhash.cpp"
 "QTextStream.cpp"
 "qfloat16.cpp"
 "QDebug.cpp"
 "qproperty.cpp"
 "qobject.cpp"
)
#file(GLOB TEST_SOURCES "./test/*.cpp")
file(GLOB TEST_SOURCES
 #"./test/src_corelib_text_qbytearray.cpp"
 )
file(GLOB HEADERS "*.h")
file(GLOB PRIVATE_HEADERS "./private/*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Header Files/Private" FILES ${PRIVATE_HEADERS})
source_group("Source Files" FILES ${SOURCES})
source_group("Source Files/Test" FILES ${TEST_SOURCES})

# Set the output directory for the dynamic library
add_library(${MODULE_NAME} SHARED ${SOURCES} ${HEADERS} ${PRIVATE_HEADERS} ${TEST_SOURCES})

# Specify include directories for header file lookup
target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ZLib
)

# Add preprocessor definitions (precompiled macros)
target_compile_definitions(${MODULE_NAME} PRIVATE
    QT_BUILD_CORE_LIB
)

# Debug postfix for debug builds
set_target_properties(${MODULE_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)

# Define UNICODE and _UNICODE for all targets
add_compile_definitions(UNICODE _UNICODE)
