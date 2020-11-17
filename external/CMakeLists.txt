message( "Download External Dependencies" )

set( EXTERNAL_TMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.temporary")
set( EXTERNAL_STAMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.stamp")
set( EXTERNAL_LOG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.log" )

include(ExternalProject)

# Instal the Google Test Framework
        set( EXTERNAL_PROJECT_NAME ext_googletest )

	# Configure Build 
	set( EXTERNAL_CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF  )

	# Redirect installation to project directory, instead of /usr/local
	if( $CROSS_COMPILING )
		list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )
	endif()

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY https://github.com/google/googletest
                GIT_TAG master
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

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

return()

# Instal the Mosquitto Library
        set( EXTERNAL_PROJECT_NAME ext_mosquitto )

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS -DDOCUMENTATION=OFF  )
	list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY  https://github.com/eclipse/mosquitto.git
                GIT_TAG master
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

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
                ALWAYS TRUE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
#		INSTALL_COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/config/mosquitto.conf /usr/local/etc/mosquitto
                COMMAND ldconfig )

# Instal the TinyXML Library
        set( EXTERNAL_PROJECT_NAME ext_tinyxml2 )

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS "" )
	list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY  https://github.com/leethomason/tinyxml2.git
                GIT_TAG master
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

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
	list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
                GIT_TAG master
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

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

	# Configure Build
	set( EXTERNAL_CMAKE_ARGS "" )
#	Custom Install Command will take care of this
#	list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
		GIT_REPOSITORY https://github.com/digint/tinyfsm
		GIT_TAG master

                UPDATE_DISCONNECTED ON

		UPDATE_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/include/tinyfsm.hpp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/externals/include

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
	set( EXTERNAL_CMAKE_ARGS -DSPDLOG_BUILD_TESTS=OFF )
	list( APPEND EXTERNAL_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/external )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
 		GIT_REPOSITORY https://github.com/gabime/spdlog.git
		GIT_TAG "v1.6.0"
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

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

                UPDATE_DISCONNECTED ON

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

