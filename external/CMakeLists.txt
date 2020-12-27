Message( "Download External Dependencies" )

include(ExternalProject)

# Storage location for build and install files
set( EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# Define generated directories
set( EXTERNAL_TMP_DIR  "${EXTERNAL_DIR}/.temporary")
set( EXTERNAL_LOG_DIR  "${EXTERNAL_DIR}/.log" )
set( EXTERNAL_STAMP_DIR "${EXTERNAL_DIR}/.stamp")

# Allow automatic checkout and rebuild
set( DISCONNECT OFF )

# Redirect installation to project directory, instead of /usr/local
set( EXTERNAL_BUILD_ARGS "" )

# Configure C++-Compiler
#list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_CXX_COMPILER:string=/usr/bin/${CMAKE_CXX_COMPILER}" )

# Configure General Cross Compiler Settings
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_SYSROOT=${CMAKE_SYSROOT}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_INSTALL_PREFIX=${EXTERNAL_DIR}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=${CMAKE_FIND_ROOT_PATH_MODE_PROGRAM}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY}" )

# Include external projects
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mosquitto.cmake )
return()
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyxml.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rapidjson.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/spdlogger.cmake )

#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.cmake )
#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cucumber.cmake )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generator.cmake )
