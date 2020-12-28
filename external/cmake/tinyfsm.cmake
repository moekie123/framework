include(ExternalProject)

# Install Tiny Finite State Machine
set( EXTERNAL_PROJECT_NAME ext_tinyfsm )

# Configure build arguments
set( EXTERNAL_CMAKE_ARGS "" )

# Create external project
ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
	GIT_REPOSITORY https://github.com/digint/tinyfsm
	GIT_TAG master

	UPDATE_DISCONNECTED ${DISCONNECT}

	UPDATE_COMMAND ""
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND cmake -E copy ${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}/include/tinyfsm.hpp ${EXTERNAL_DIR}/output/include
	TEST_COMMAND ""

	DOWNLOAD_DIR    "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	SOURCE_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	BINARY_DIR      "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"
	INSTALL_DIR     "${EXTERNAL_DIR}/${EXTERNAL_PROJECT_NAME}"

	TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
	LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"
)

# GLibc must be build before googletest can be build because of the phread.h dependency
ExternalProject_Add_StepDependencies( ${EXTERNAL_PROJECT_NAME} install "ext_glibc" )
