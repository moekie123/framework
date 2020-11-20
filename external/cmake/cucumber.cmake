include(ExternalProject)

# Instal the Google Test Framework
set( EXTERNAL_PROJECT_NAME ext_cucumber )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS -DBUILD_SHARED_LIBS=ON )

# Add cross compiler arguments to build arguments
if( CROSS_COMPILING )
	list( APPEND EXTERNAL_CMAKE_ARGS ${EXTERNAL_CROSS_COMPILE_ARGS} )
endif()

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/cucumber/cucumber-cpp.git
	GIT_TAG master
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

	CMAKE_ARGS 	${EXTERNAL_CMAKE_ARGS} 
)

# Refresh dynamic link libraries ( only on Raspberry Pi hardware )
if( NOT CROSS_COMPILING )
	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
		ALWAYS FALSE
		DEPENDEES "install"
		COMMENT "Link Dynamic Libraries"
		COMMAND ldconfig )
endif()
