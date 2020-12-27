include(ExternalProject)

# Install Rapid JSON
set( EXTERNAL_PROJECT_NAME ext_rapidjson )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS "" )

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
	GIT_TAG master
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED ${DISCONNECT}

# Customize the build command such that =march is compaatible
# - Figrue wich build flags are used at the momemtn
#	BUILD_COMMAND ""

	DOWNLOAD_DIR    "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"
	
	CMAKE_ARGS 	-DCMAKE_CXX_COMPILER=/usr/bin/${CMAKE_CXX_COMPILER}

			-DCMAKE_SYSROOT=${CMAKE_SYSROOT}

			-DCMAKE_INSTALL_PREFIX=${EXTERNAL_DIR}
			-DCMAKE_INSTALL_LIBDIR=${EXTERNAL_DIR}/library 
			-DCMAKE_INSTALL_INCLUDEDIR=${EXTERNAL_DIR}/include
			
			-DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=${CMAKE_FIND_ROOT_PATH_MODE_PROGRAM} 
			-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=${CMAKE_FIND_ROOT_PATH_MODE_INCLUDE} 
			-DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=${CMAKE_FIND_ROOT_PATH_MODE_LIBRARY} 

			-DRAPIDJSON_BUILD_DOC=OFF
			-DRAPIDJSON_BUILD_EXAMPLES=OFF
			-DRAPIDJSON_BUILD_TESTS=OFF 
)
