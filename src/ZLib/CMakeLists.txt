# Set the module name
set(MODULE_NAME ZLib)

# Collect source and header files
file(GLOB SOURCES "*.c")
file(GLOB HEADERS "*.h")

# Organize files into filters for Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

# Set the output directory for the dynamic library
add_library(${MODULE_NAME} SHARED ${SOURCES} ${HEADERS})

# Add preprocessor definitions (precompiled macros)
target_compile_definitions(${MODULE_NAME} PRIVATE
    QT_BUILD_CORE_LIB
)

# Specify include directories for header file lookup
target_include_directories(${MODULE_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../Qt
    ${CMAKE_CURRENT_SOURCE_DIR}/../Qt/QtCore
)

#qt_internal_add_3rdparty_library(BundledZLIB
#    STATIC
#    SKIP_AUTOMOC
#    SOURCES
#        src/adler32.c
#        src/compress.c
#        src/crc32.c
#        src/crc32.h
#        src/deflate.c
#        src/deflate.h
#        src/gzclose.c
#        src/gzguts.h
#        src/gzlib.c
#        src/gzread.c
#        src/gzwrite.c
#        src/infback.c
#        src/inffast.c
#        src/inffast.h
#        src/inffixed.h
#        src/inflate.c
#        src/inflate.h
#        src/inftrees.c
#        src/inftrees.h
#        src/trees.c
#        src/trees.h
#        src/uncompr.c
#        src/zconf.h
#        src/zlib.h
#        src/zutil.c
#        src/zutil.h
#    DEFINES
#        QT_BUILD_CORE_LIB
#    INCLUDE_DIRECTORIES
#        $<TARGET_PROPERTY:Core,INCLUDE_DIRECTORIES>
#)

#qt_internal_add_sync_header_dependencies(BundledZLIB Core)

#qt_disable_warnings(BundledZLIB)

#qt_set_symbol_visibility_hidden(BundledZLIB)

#qt_internal_add_3rdparty_header_module(ZlibPrivate
#    EXTERNAL_HEADERS
#        src/zlib.h
#        src/zconf.h
#)
