include(ExternalProject)

# Instal the Boost Framework
set( EXTERNAL_PROJECT_NAME ext_boost )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS "" )

# Add cross compiler arguments to build arguments
if( CROSS_COMPILING )
	list( APPEND EXTERNAL_CMAKE_ARGS ${EXTERNAL_COMPILER} )
endif()	

ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/boostorg/boost/
	GIT_TAG boost-1.74.0
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	CONFIGURE_COMMAND ""
	
	BUILD_COMMAND bjam --with-regex toolset=arm-linux-gnueabihf-g++  variant=debug link=static install --prefix=/tmp/boostinstall

	INSTALL_COMMAND = ""

	DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
#	BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

	CMAKE_ARGS 	${EXTERNAL_CMAKE_ARGS}

	BUILD_IN_SOURCE ON 
)

# Refresh dynamic link libraries ( only on Raspberry Pi hardware )
if( NOT CROSS_COMPILING )
	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
		ALWAYS FALSE
		DEPENDEES "install"
		COMMENT "Link Dynamic Libraries"
		COMMAND ldconfig )
endif()
