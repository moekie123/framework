Message( "Download External Dependencies" )

include(ExternalProject)

# Storage location for build and install files
set( EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# Define generated directories
set( EXTERNAL_TMP_DIR  "${EXTERNAL_DIR}/.temporary")
set( EXTERNAL_LOG_DIR  "${EXTERNAL_DIR}/.log" )
set( EXTERNAL_STAMP_DIR "${EXTERNAL_DIR}/.stamp")

# Allow automatic checkout and rebuild
set( DISCONNECT ON )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/glibc.cmake )

# Include external projects
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mosquitto.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyxml.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rapidjson.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/spdlogger.cmake )

#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.cmake )
#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cucumber.cmake )

include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/generator.cmake )
