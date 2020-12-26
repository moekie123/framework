include(ExternalProject)

# Install Version Generator
set( EXTERNAL_PROJECT_NAME generator )

ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/erichschroeter/cmake-auto-increment-build-number.git
	GIT_TAG master
	GIT_PROGRESS ON

	UPDATE_DISCONNECTED EXTERNAL_UPDATE

	CONFIGURE_COMMAND ""
	BUILD_COMMAND gcc -o ${EXTERNAL_PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/C_binary_example/generate.c
	INSTALL_COMMAND mv ${EXTERNAL_PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
	TEST_COMMAND ""

	DOWNLOAD_DIR    "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"

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

