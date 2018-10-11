add_library(bigfile
    SmallFile.cpp
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

