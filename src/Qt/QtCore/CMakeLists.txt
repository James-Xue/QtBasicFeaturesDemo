# Set the module name
set(MODULE_NAME QtCore)

# Collect source and header files
#file(GLOB SOURCES "*.cpp")
file(GLOB SOURCES
    # Base classes
    "cstrfuns.cpp"
    "qtmiscutils.cpp"
    "qcompare.cpp"
    "qtprivate.cpp"
    "qarraydata.cpp"
    "qbytearray.cpp"
    "qbytearrayview.cpp"
    "qbytearraymatcher.cpp"
    "qunicodetables.cpp"
    # "qchar.cpp"
    # "qobject.cpp"
    # "qmetaobject.cpp"
    # "qproperty.cpp"
    # "qmetatype.cpp"
    
    # Container classes
    # "qstring.cpp"
    # "qstringview.cpp"
    # "qlocale_tools.cpp"
    # "qstringconverter.cpp"
    # "qlist.cpp"
    # "qvector.cpp"
    # "qmap.cpp"
    # "qset.cpp"
    # "qpair.cpp"
    # "qvariant.cpp"
    # "qhash.cpp"
    # "qstringlist.cpp"
    # "qfloat16.cpp"
    # "qdatastream.cpp"
    # "qtextStream.cpp"

    # Time and date classes
    # "qdatetime.cpp"
    # "qtimer.cpp"
    # "qdatetime.cpp"
    # "qtimezone.cpp"
    # "qcalendar.cpp"
    # "qjalalicalendar.cpp"
    # "qhijricalendar.cpp"
    # "qislamiccivilcalendar.cpp"
    # "qjuliancalendar.cpp"
    # "qgregoriancalendar.cpp"
    # "qromancalendar.cpp"
    # "qmilankoviccalendar.cpp"
    # "qdeadlinetimer.cpp"

    # Thread and synchronization classes
    "qatomic.cpp"
    # "qthread.cpp"
    # "qmutex.cpp"
    # "qwaitcondition_win.cpp"
    # "qreadwritelock.cpp"
    # "qsemaphore.cpp"
    # "qthreadpool.cpp"
    # "qfuture.cpp"
    # "qfuturewatcher.cpp"

    # File and directory classes
    # "qfile.cpp"
    # "qiodevice.cpp"
    # "qbuffer.cpp"
    # "qdir.cpp"
    # "qfileinfo.cpp"
    # "qfiledevice.cpp"
    # "qfsfileengine.cpp"

    # internationalization and localization classes
    # "qlocale.cpp"
    # "qtranslator.cpp"
    # "qromancalendar.cpp"
    # "qgregoriancalendar.cpp"

    # Event and signal classes
    # "qcoreevent.cpp"
    # "qevent.cpp"

    # UI classes
    # "qfiledialog.cpp"
    # "qfileiconprovider.cpp"
    # "qmessagebox.cpp"
    # "qinputdialog.cpp"
    # "qprogressdialog.cpp"

    # Debugging and logging classes
    "qassert.cpp"
    # "qsystemerror.cpp"
    # "qlogging.cpp"
    # "qdebug.cpp"

    # Miscellaneous classes
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
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${CMAKE_CURRENT_SOURCE_DIR}/../../ZLib
    ${CMAKE_CURRENT_SOURCE_DIR}/../../DoubleConversion
)

# Link against the QtCore dynamic library
target_link_libraries(${MODULE_NAME} PRIVATE ZLib)

# Add preprocessor definitions (precompiled macros)
target_compile_definitions(${MODULE_NAME} PRIVATE
    QT_BUILD_CORE_LIB
)

# Debug postfix for debug builds
set_target_properties(${MODULE_NAME} PROPERTIES
    DEBUG_POSTFIX "_d"
)

# Add compile options to generate preprocessed files with comments for the entire module
# if (MSVC)
#     foreach(SOURCE_FILE ${SOURCES})
#         # Get the file name without extension
#         get_filename_component(FILE_NAME ${SOURCE_FILE} NAME_WE)
#         # Set the output path for the preprocessed file
#         set(PREPROCESSED_FILE "${CMAKE_CURRENT_BINARY_DIR}/${FILE_NAME}.i")
#         # Add compile options for each source file
#         set_source_files_properties(${SOURCE_FILE} PROPERTIES COMPILE_FLAGS "/P /C /Fi${PREPROCESSED_FILE}")
#     endforeach()
# endif()

# Add compile options to generate preprocessed files with comments for the entire module
# target_compile_options(${MODULE_NAME} PRIVATE /P /C)

# add_custom_target(preprocess ALL
#     COMMAND ${CMAKE_CXX_COMPILER} /P /C /Fi${CMAKE_CURRENT_BINARY_DIR}/preprocessed_file.i ${CMAKE_CURRENT_SOURCE_DIR}/source_file.cpp
#     COMMENT "Generating preprocessed file with comments"
# )
