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

add_subdirectory (bigfile)
#add_subdirectory (study)
#add_subdirectory (doc)

enable_testing() 
#find_package(GTest REQUIRED) 
add_subdirectory (test) 

# Show important CMAKE variables
MESSAGE( STATUS "CMAKE_C_COMPILER:       " ${CMAKE_C_COMPILER} )
MESSAGE( STATUS "CMAKE_CXX_COMPILER:     " ${CMAKE_CXX_COMPILER} )
MESSAGE( STATUS "CMAKE_INSTALL_PREFIX:   " ${CMAKE_INSTALL_PREFIX} )
#MESSAGE( STATUS "DOXYGEN_EXECUTABLE:     " ${DOXYGEN_EXECUTABLE} )
#MESSAGE( STATUS "DOXYGEN_DOT_EXECUTABLE: " ${DOXYGEN_DOT_EXECUTABLE} )
