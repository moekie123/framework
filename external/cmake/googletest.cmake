include(ExternalProject)

# Install the Google Test Framework
set( EXTERNAL_PROJECT_NAME ext_googletest )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF )

# Add configure install directories
list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_LIBDIR=${EXTERNAL_DIR}/library ) 
list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_INCLUDEDIR=${EXTERNAL_DIR}/include )

# Add cross compiler arguments to build arguments
list( APPEND EXTERNAL_CMAKE_ARGS ${EXTERNAL_BUILD_ARGS} )

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/google/googletest
	GIT_TAG master
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	DOWNLOAD_DIR    "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"

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

