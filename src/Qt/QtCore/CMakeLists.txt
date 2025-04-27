# Set the module name
set(MODULE_NAME QtCore)

# Collect source and header files
#file(GLOB SOURCES "*.cpp")
file(GLOB SOURCES
    # Base classes
    "qobject.cpp"
    "qmetaobject.cpp"
    "qproperty.cpp"
    "qmetatype.cpp"

    # Container classes
    #"qchar.cpp"
    "qstring.cpp"
    "qstringview.cpp"
    "qlocale_tools.cpp"
    "qstringconverter.cpp"
    #"qlist.cpp"
    #"qvector.cpp"
    #"qmap.cpp"
    #"qset.cpp"
    #"qpair.cpp"
    "qvariant.cpp"
    "qbytearray.cpp"
    "qbytearraymatcher.cpp"
    "qhash.cpp"
    "qstringlist.cpp"
    "qfloat16.cpp"
    "qarraydata.cpp"
    "qdatastream.cpp"
    "qtextStream.cpp"

    # Time and date classes
    "qdatetime.cpp"
    "qtimer.cpp"
    "qdatetime.cpp"

    # Thread and synchronization classes
    "qthread.cpp"
    "qmutex.cpp"
    "qwaitcondition_win.cpp"
    "qreadwritelock.cpp"
    "qsemaphore.cpp"
    "qthreadpool.cpp"
    #"qfuture.cpp"
    "qfuturewatcher.cpp"

    # File and directory classes
    "qfile.cpp"
    "qdir.cpp"
    "qfileinfo.cpp"
    "qfiledevice.cpp"
    "qfsfileengine.cpp"
    
    # internationalization and localization classes
    "qlocale.cpp"
    "qtranslator.cpp"
    
    # UI classes
    #"qfiledialog.cpp"
    #"qfileiconprovider.cpp"
    #"qmessagebox.cpp"
    #"qinputdialog.cpp"
    #"qprogressdialog.cpp"

    # Miscellaneous classes
    "qlogging.cpp"
    "qassert.cpp"
    "qdebug.cpp"
)

# Check if any required files are missing
if (SOURCES STREQUAL "" OR HEADERS STREQUAL "" OR PRIVATE_HEADERS STREQUAL "")
    message(FATAL_ERROR "Error: Required source or header files are missing!")
endif()

#file(GLOB TEST_SOURCES "./test/*.cpp")
file(GLOB TEST_SOURCES
 #"./test/src_corelib_text_qbytearray.cpp"
 )
file(GLOB HEADERS "*.h")
file(GLOB PRIVATE_HEADERS "./private/*.h")

# Check if any required files are missing
if (SOURCES STREQUAL "" OR HEADERS STREQUAL "" OR PRIVATE_HEADERS STREQUAL "")
    message(FATAL_ERROR "Error: Required source or header files are missing!")
endif()

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
    ${CMAKE_CURRENT_SOURCE_DIR}/../../DoubleConversion
)

# Add preprocessor definitions (precompiled macros)
target_compile_definitions(${MODULE_NAME} PRIVATE
    QT_BUILD_CORE_LIB
)

# Debug postfix for debug builds
set_target_properties(${MODULE_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)