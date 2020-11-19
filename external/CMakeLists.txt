Message( "Download External Dependencies" )

set( EXTERNAL_TMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.temporary")
set( EXTERNAL_STAMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.stamp")
set( EXTERNAL_LOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.log" )

set( EXTERNAL_INSTALL_PREFIX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/externals )

set( EXTERNAL_UPDATE OFF )
include(ExternalProject)

# Redirect installation to project directory, instead of /usr/local
if( CROSS_COMPILING )
	# Configure C-Compiler
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} )

	# Configure C++-Compiler
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} )

	# Configure General Cross Compiler Settings
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PREFIX} )
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_SYSROOT=${CMAKE_SOURCE_DIR}/kernel/linux )

	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_FIND_ROOT_PATH_MODE_PROGRAM=NEVER )
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY )
	list( APPEND EXTERNAL_CROSS_COMPILE_ARGS -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY )
endif()

include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/googletest.cmake )
include( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mosquitto.cmake )

return()

# Instal the TinyXML Library
        set( EXTERNAL_PROJECT_NAME ext_tinyxml2 )

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS "" )

	# Redirect installation to project directory, instead of /usr/local
	if( CROSS_COMPILING )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PREFIX} )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_SYSROOT=${CMAKE_SOURCE_DIR}/kernel/linux )
	endif()

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY  https://github.com/leethomason/tinyxml2.git
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

	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS FALSE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )

# Instal the RapidJson Library
        set( EXTERNAL_PROJECT_NAME ext_rapidjson )

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS "" )
	
	# Redirect installation to project directory, instead of /usr/local
	if( CROSS_COMPILING )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PREFIX} )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_CROSSCOMPILING=ON )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_SYSROOT=${CMAKE_SOURCE_DIR}/kernel/linux )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_CXX_FLAGS="-march=armv7") 
	endif()

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
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

        ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS FALSE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )

# Install the tinyfsm library
	set( EXTERNAL_PROJECT_NAME ext_tinyfsm )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
		GIT_REPOSITORY https://github.com/digint/tinyfsm
		GIT_TAG master

                UPDATE_DISCONNECTED EXTERNAL_UPDATE

		UPDATE_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/include/tinyfsm.hpp ${EXTERNAL_INSTALL_PREFIX}/include

                DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

                TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

		TEST_COMMAND ""
	)

# Instal Speed Logger
        set( EXTERNAL_PROJECT_NAME ext_spdlogger )

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS -DSPDLOG_BUILD_SHARED=ON )
	list( APPEND EXTERNAL_CMAKE_ARGS -DSPDLOG_BUILD_TESTS=OFF )
	list( APPEND EXTERNAL_CMAKE_ARGS -DSPDLOG_BUILD_TESTS_HO=OFF )

	# Redirect installation to project directory, instead of /usr/local
	if( CROSS_COMPILING )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} )
#		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_PREFIX} )
	endif()

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
 		GIT_REPOSITORY https://github.com/gabime/spdlog.git
		GIT_TAG "v1.6.0"
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

        ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS FALSE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )


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

