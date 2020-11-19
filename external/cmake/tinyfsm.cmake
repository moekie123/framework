include(ExternalProject)

# Instal the Google Test Framework
set( EXTERNAL_PROJECT_NAME ext_tinyfsm )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS "" )

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/digint/tinyfsm
	GIT_TAG master

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/include/tinyfsm.hpp ${EXTERNAL_INSTALL_PREFIX}/include
	TEST_COMMAND ""

	DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

)

# Refresh dynamic link libraries ( only on Raspberry Pi hardware )
if( NOT CROSS_COMPILING )
	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
		ALWAYS FALSE
		DEPENDEES "install"
		COMMENT "Link Dynamic Libraries"
		COMMAND ldconfig )
endif()
