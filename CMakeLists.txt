# CMake file for BIGFILE project, Igor Lesik 2018.

cmake_minimum_required (VERSION 3.10)

# CMakeLists files in this project can refer to the root source directory
# of the project as ${BIGFILE_SOURCE_DIR} and to the root binary directory
# of the project as ${BIGFILE_BINARY_DIR}.
project (BIGFILE
    VERSION 0.1
    LANGUAGES C CXX
)

# Require C++17
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

# Install inside build directory
set (CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

option(ENABLE_TESTS "Build tests?" ON)
option(ENABLE_DOCS  "Build docs?"  ON)

add_subdirectory (bigfile)
#add_subdirectory (study)

if (ENABLE_DOCS)
    #add_subdirectory (doc)
endif (ENABLE_DOCS)

if (ENABLE_TESTS)
    enable_testing() 
    #find_package(GTest REQUIRED) 
    add_subdirectory (test) 
endif (ENABLE_TESTS)

# Show important CMAKE variables
message( STATUS "CMAKE_C_COMPILER:       " ${CMAKE_C_COMPILER} )
message( STATUS "CMAKE_CXX_COMPILER:     " ${CMAKE_CXX_COMPILER} )
message( STATUS "CMAKE_INSTALL_PREFIX:   " ${CMAKE_INSTALL_PREFIX} )
#MESSAGE( STATUS "DOXYGEN_EXECUTABLE:     " ${DOXYGEN_EXECUTABLE} )
#MESSAGE( STATUS "DOXYGEN_DOT_EXECUTABLE: " ${DOXYGEN_DOT_EXECUTABLE} )

if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "DEBUG"))
    message("Build type is DEBUG")
endif ()
