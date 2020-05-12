message( "Download External Dependencies" )

find_package(PkgConfig)
include(ExternalProject)

set( ALL_EXTERNALS_BUILD ON PARENT_SCOPE )

#Install the googletest framework
ExternalProject_Add( gexternal
	PREFIX ${CMAKE_SOURCE_DIR}/external/googletest
	CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON"
	GIT_REPOSITORY https://github.com/google/googletest
)

ExternalProject_Add_Step( gexternal refresh
	ALWAYS TRUE
	DEPENDEES "install"
	COMMENT "refresh shared library cache" 
	COMMAND ldconfig )

pkg_search_module(GTEST gtest_main)
if( GTEST_FOUND )
	message( STATUS "Google Test [${GTEST_VERSION}] already installed" )
endif()

# Install the mosquitto library
#find_package( Mosquitto )
pkg_search_module( MOSQUITTO REQUIRED libmosquitto )
if( NOT MOSQUITTO_FOUND )
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

else()
	message( STATUS "Mosquitto [${MOSQUITTO_VERSION}] already installed" )
endif()

# Install the tinyxml library
pkg_search_module( TINYXML2 REQUIRED tinyxml2 )
if( NOT TINYXML2_FOUND )
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

else()
	message( STATUS "TinyXml2 [${TINYXML2_VERSION}] already installed" )
endif()

# Install the rapid json library
#find_package( RapidJSON )
pkg_search_module( RAPIDJSON REQUIRED RapidJSON )
if( NOT RAPIDJSON_FOUND )
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

else()
	message( STATUS "RapidJson [${RAPIDJSON_VERSION}] already installed" )
endif()

# Install the tinyfsm library
IF( NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tinyfsm )
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_FSM
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm
		GIT_REPOSITORY https://github.com/digint/tinyfsm
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
    		VERSION 0.2
    		COMPATIBILITY AnyNewerVersion
	)

	# Create Package Config for the library
	include(CMakePackageConfigHelpers)
	configure_package_config_file(
    		"${CMAKE_CURRENT_SOURCE_DIR}/cmake/tinyfsm.cmake.in"
    		"${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cmake/tinyfsm.cmake"
    		INSTALL_DESTINATION lib/cmake/tinyfsm
	)

	# Copy the files to the installion directories
	install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/cmake/tinyfsm.cmake" DESTINATION /lib/cmake/tinyfsm )
	install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm/src/EXTERNAL_FSM/include/  DESTINATION /usr/local/include )

else()
	message( STATUS "TinyFsm already installed" )
	include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm/src/EXTERNAL_FSM/include/tinyfsm.hpp )
endif()


IF( NOT EXISTS ${CMAKE_SOURCE_DIR}/external/version )
	set( ALL_EXTERNALS_BUILD OFF PARENT_SCOPE )

	ExternalProject_Add( EXTERNAL_VERSION
		PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/version
		INSTALL_COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/version/src/EXTERNAL_VERSION/generate.c ${CMAKE_CURRENT_SOURCE_DIR}/version/
		GIT_REPOSITORY https://github.com/erichschroeter/cmake-auto-increment-build-number.git
	)

else()
	message( STATUS "Version generator already installed" )
	add_executable( generator ${CMAKE_CURRENT_SOURCE_DIR}/version/generate.c )

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
