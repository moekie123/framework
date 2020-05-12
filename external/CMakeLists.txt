message( "Download External Dependencies" )

find_package(PkgConfig)
include(ExternalProject)

set( ALL_EXTERNALS_BUILD ON PARENT_SCOPE )

# Instal the Google Test Framework
add_library( ext-gtest INTERFACE )
pkg_search_module( GTEST gtest_main )
if( NOT GTEST_FOUND )
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

	add_dependencies( ext-gtest EXTERNAL_GTEST )
else()
	message( STATUS "Google Test [${GTEST_VERSION}] already installed" )
endif()

# Install the mosquitto library
add_library( ext-mqtt INTERFACE )
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

	add_dependencies( ext-mqtt EXTERNAL_MQTT )
else()
	message( STATUS "Mosquitto [${MOSQUITTO_VERSION}] already installed" )
endif()

# Install the tinyxml library
add_library( ext-xml INTERFACE )
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

	add_dependencies( ext-xml EXTERNAL_XML )
else()
	message( STATUS "TinyXml2 [${TINYXML2_VERSION}] already installed" )
endif()

# Install the rapid json library
add_library( ext-json INTERFACE )
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

	add_dependencies( ext-json EXTERNAL_JSON )
else()
	message( STATUS "RapidJson [${RAPIDJSON_VERSION}] already installed" )
endif()

# Install the tinyfsm library
add_library( ext-fsm INTERFACE )
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

	add_dependencies( ext-fsm EXTERNAL_FSM )
else()
	message( STATUS "TinyFsm already installed" )
#	include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/tinyfsm/src/EXTERNAL_FSM/include/tinyfsm.hpp )
endif()


# Instal Version Generator
add_library( ext-version INTERFACE )
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

	# CMake Refresh Trick
	# 	With the 'EXTERNAL_VERSION-Refresh'-Step the CMakeLists.txt, in version, will be modified
	#	Because this file has been changed CMake will rebuild the project 
	#	During the rebuild the code will fall in the else-statmenet
	ExternalProject_Add_Step( EXTERNAL_VERSION refresh
		ALWAYS TRUE	
		DEPENDEES "build"
		COMMENT "Copy downloaded files" 
		COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/version/src/EXTERNAL_VERSION/generate.c ${CMAKE_CURRENT_SOURCE_DIR}/version/
		COMMAND echo "" >> ${CMAKE_CURRENT_SOURCE_DIR}/version/CMakeLists.txt
	)

	add_custom_target( Generate DEPENDS EXTERNAL_VERSION )
	add_subdirectory( version )
else()
	message( STATUS "Version generator is installed" )

	# Create Generator
	add_executable( generator ${CMAKE_CURRENT_SOURCE_DIR}/version/generate.c )
	add_dependencies( generator ext-version )

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


