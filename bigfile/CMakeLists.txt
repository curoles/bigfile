find_package(ZLIB  REQUIRED)
if (NOT ZLIB_FOUND)
    message(FATAL_ERROR "No ZLIB library found/installed")
endif (NOT ZLIB_FOUND)

#find_package(Gpgme REQUIRED)
#if (NOT GPGME_FOUND)
#    message(FATAL_ERROR "No Gpgme library found/installed")
#endif (NOT GPGMEB_FOUND)


add_library(bigfile
    StdioFile.cpp
    SmallFile.cpp
    BigFile.cpp
    FileExtension.cpp
    Zlib.cpp
    Gpg.cpp
)

target_compile_options(bigfile PRIVATE -Wall)

target_include_directories(bigfile
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(bigfile
    -lstdc++fs
    -lz
)

set(BIGFILE_PUBLIC_HEADER_FILES 
    StdioFile.h
)

set_target_properties(bigfile
PROPERTIES 
    VERSION 0.1.0
    PUBLIC_HEADER "${BIGFILE_PUBLIC_HEADER_FILES}"
)

install(TARGETS bigfile
    ARCHIVE
        DESTINATION lib
    PUBLIC_HEADER
        DESTINATION include/bigfile
)

