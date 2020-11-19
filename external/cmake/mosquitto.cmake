include(ExternalProject)

# Instal the Mosquitto Library
set( EXTERNAL_PROJECT_NAME ext_mosquitto )

# Configure Build
set( EXTERNAL_CMAKE_ARGS -DDOCUMENTATION=OFF  )

# TODO: These should be able to be turned IN
message( NOTICE "-!- Mosquite is not using TLS -!-" )
list( APPEND EXTERNAL_CMAKE_ARGS -DWITH_TLS=OFF )

message( NOTICE "-!- Mosquite is not using THREADING -!-" )
list( APPEND EXTERNAL_CMAKE_ARGS -DWITH_THREADING=OFF )

# Add cross compiler arguments to build arguments
if( CROSS_COMPILING )
	list( APPEND EXTERNAL_CMAKE_ARGS ${EXTERNAL_CROSS_COMPILE_ARGS} )
endif()

ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY  https://github.com/eclipse/mosquitto.git
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
