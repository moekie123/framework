message( "Download External Dependencies" )

include(ExternalProject)

# Instal the Google Test Framework
        set( EXTERNAL_PROJECT_NAME ext_googletest )

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

                CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON"
        )

        ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS FALSE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )

# Instal the Mosquitto Library
        set( EXTERNAL_PROJECT_NAME ext_mosquitto )

        ExternalProject_Add( ${EXTERNAL_PROJECT_NAME}
                GIT_REPOSITORY  https://github.com/eclipse/mosquitto.git
                GIT_TAG master
                GIT_PROGRESS ON

                UPDATE_DISCONNECTED ON

		INSTALL_COMMAND cmake -E copy ${CMAKE_SOURCE_DIR}/config/mosquitto.conf /usr/local/etc/mosquitto

                DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

                TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

                CMAKE_ARGS "-DDOCUMENTATION=OFF"
        )

	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS TRUE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )


# Instal the TinyXML Library
        set( EXTERNAL_PROJECT_NAME ext_tinyxml2 )

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
	)

	ExternalProject_Add_Step( ${EXTERNAL_PROJECT_NAME} link
                ALWAYS FALSE
                DEPENDEES "install"
                COMMENT "Link Dynamic Libraries"
                COMMAND ldconfig )

# Instal the RapidJson Library
        set( EXTERNAL_PROJECT_NAME ext_rapidjson )

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

                UPDATE_DISCONNECTED ON

		UPDATE_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND cmake -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}/include/tinyfsm.hpp /usr/local/include/ 

                DOWNLOAD_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                SOURCE_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                BINARY_DIR      "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"
                INSTALL_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/${EXTERNAL_PROJECT_NAME}"

                TMP_DIR         "${EXTERNAL_TMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                STAMP_DIR       "${EXTERNAL_STAMP_DIR}/${EXTERNAL_PROJECT_NAME}"
                LOG_DIR         "${EXTERNAL_LOG_DIR}/${EXTERNAL_PROJECT_NAME}"

#	message( STATUS "CATCH 22 - INSTAL REQUIRED !!!!!!! , but build fails before, because it is missing the install" )
#	install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cmake/tinyfsm.cmake" DESTINATION /lib/cmake/tinyfsm )
#	install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm/src/EXTERNAL_FSM/include/  DESTINATION /usr/local/include )

		TEST_COMMAND ""
	)


# Instal Speed Logger
        set( EXTERNAL_PROJECT_NAME ext_spdlogger )

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
       
		CMAKE_ARGS "-DSPDLOG_BUILD_SHARED=ON"
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

