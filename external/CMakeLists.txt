Message( "Download External Dependencies" )

include(ExternalProject)

# Storage location for build and install files
set( EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}" )

# Define generated directories
set( EXTERNAL_TMP_DIR  "${EXTERNAL_DIR}/.temporary")
set( EXTERNAL_LOG_DIR  "${EXTERNAL_DIR}/.log" )
set( EXTERNAL_STAMP_DIR "${EXTERNAL_DIR}/.stamp")

# Allow automatic checkout and rebuild
set( EXTERNAL_UPDATE OFF )

# Redirect installation to project directory, instead of /usr/local
set( EXTERNAL_BUILD_ARGS "" )

# Configure C++-Compiler
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}" )

# Configure General Cross Compiler Settings
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_INSTALL_PREFIX=${EXTERNAL_DIR}" )

list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_SYSROOT=${CMAKE_SYSROOT}" )

list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=${CMAKE_FIND_ROOT_PATH_MODE_PROGRAM}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE}" )
list( APPEND EXTERNAL_BUILD_ARGS " -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY}" )

# Test Enviroments
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mosquitto.cmake )

return()

# Other third-party libraries
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyxml.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/rapidjson.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/spdlogger.cmake )

#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/boost.cmake )
#include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cucumber.cmake )

# Install Version Generator
set( EXTERNAL_PROJECT_NAME generator )

ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/erichschroeter/cmake-auto-increment-build-number.git
	GIT_TAG master
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	CONFIGURE_COMMAND ""
	BUILD_COMMAND gcc -o ${EXTERNAL_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/C_binary_example/generate.c
	INSTALL_COMMAND mv ${EXTERNAL_PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
	TEST_COMMAND ""

	DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

)

# Generate Version Control Header
add_custom_target( version ALL
	COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXTERNAL_PROJECT_NAME}
		 -P "FRAMEWORK"
		 -M "${VERSION_MAJOR}"
		 -m ${VERSION_MINOR}
		 -p ${VERSION_PATCH}
		 -a "${VERSION_META}"
		 -F "${CMAKE_SOURCE_DIR}/.buildnumber"
		 -i
	> ${CMAKE_SOURCE_DIR}/include/version.h

	DEPENDS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXTERNAL_PROJECT_NAME}"
	COMMENT "Generating version tags"
	VERBATIM
)
add_dependencies( version ${EXTERNAL_PROJECT_NAME} )

