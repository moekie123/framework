message( "Download External Dependencies" )

include(ExternalProject)

# Instal the Google Test Framework
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	#Install the googletest framework
	ExternalProject_Add( EXTERNAL_GTEST
		PREFIX ${CMAKE_SOURCE_DIR}/external/googletest
		CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON"
		GIT_REPOSITORY https://github.com/google/googletest
	)

	ExternalProject_Add_Step( EXTERNAL_GTEST refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

# Install the mosquitto library
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_MQTT
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/mosquitto
		CMAKE_ARGS "-DDOCUMENTATION=OFF"
		GIT_REPOSITORY  https://github.com/eclipse/mosquitto.git
	)

	ExternalProject_Add_Step( EXTERNAL_MQTT refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

# Install the tinyxml library
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_XML
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2
		GIT_REPOSITORY  https://github.com/leethomason/tinyxml2.git
	)

	ExternalProject_Add_Step( EXTERNAL_XML refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

# Install the rapid json library
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_JSON
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson
		GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
	)

	ExternalProject_Add_Step( EXTERNAL_JSON refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

# Install the tinyfsm library
	ExternalProject_Add( EXTERNAL_FSM
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm
	
		GIT_REPOSITORY https://github.com/digint/tinyfsm
		GIT_TAG master

		UPDATE_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
		TEST_COMMAND ""
	)

	# Create Package Config file based on the input-file
	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
    		"${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake.in"
    		VERSION 0.3
    		COMPATIBILITY AnyNewerVersion
	)

	# Create Package Config for the library
	include(CMakePackageConfigHelpers)
	configure_package_config_file(
    		"${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake.in"
    		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cmake/tinyfsm.cmake"
    		INSTALL_DESTINATION lib/cmake/tinyfsm
	)

	message( STATUS "CATCH 22 - INSTAL REQUIRED !!!!!!! , but build fails before, because it is missing the install" )
	# Copy the files to the installion directories
#	install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cmake/tinyfsm.cmake" DESTINATION /lib/cmake/tinyfsm )
	install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm/src/EXTERNAL_FSM/include/  DESTINATION /usr/local/include )


# Instal Speed Logger
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	#Install speed logger 
	ExternalProject_Add( EXTERNAL_LOGGER
		PREFIX ${CMAKE_SOURCE_DIR}/external/logger
		CMAKE_ARGS "-DSPDLOG_BUILD_SHARED=ON"
		GIT_REPOSITORY https://github.com/gabime/spdlog.git
		GIT_TAG "v1.6.0"
	)

	ExternalProject_Add_Step( EXTERNAL_LOGGER refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

message( FATAL "Version Generator Can not be build anymore" )

# Instal Version Generator
IF( NOT EXISTS ${CMAKE_SOURCE_DIR}/external/version/generate.c )
	message( STATUS "Install version generator" )

	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_VERSION
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/version
		GIT_REPOSITORY https://github.com/erichschroeter/cmake-auto-increment-build-number.git
		UPDATE_COMMAND ""
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
		TEST_COMMAND ""
		)

	ExternalProject_Add_Step( EXTERNAL_VERSION refresh
		ALWAYS TRUE	
		DEPENDEES "build"
		COMMENT "Copy downloaded files" 
		COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/version/src/EXTERNAL_VERSION/generate.c ${CMAKE_CURRENT_SOURCE_DIR}/version/
	)

	#add_custom_target( Generate DEPENDS EXTERNAL_VERSION )
	add_dependencies( EXTERNAL_VERSION REBUILD )
else()
	message( STATUS "Version generator is installed" )

	# Create Generator
	add_executable( generator ${CMAKE_CURRENT_SOURCE_DIR}/version/generate.c )

	# Generate Version Control Header
	add_custom_target( version ALL
		COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/generator
			 -P "FRAMEWORK"
			 -M "${VERSION_MAJOR}"
			 -m ${VERSION_MINOR}
			 -p ${VERSION_PATCH}
			 -a "${VERSION_META}"
			 -F "${CMAKE_SOURCE_DIR}/.buildnumber"
			 -i
		> ${CMAKE_SOURCE_DIR}/include/version.h 

		DEPENDS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/generator
		COMMENT "Generating version tags"
		VERBATIM
	    )
	add_dependencies( version generator )
endif()
