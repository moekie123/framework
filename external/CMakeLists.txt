message( "Download External Dependencies" )

find_package(PkgConfig)
include(ExternalProject)

#Install the googletest framework

#find_package( GTest )
pkg_search_module(GTEST REQUIRED gtest_main)
if( NOT GTEST_FOUND )

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

else()
	message( STATUS "Google Test [${GTEST_VERSION}] already installed" )
endif()

# Install the mosquitto library
#find_package( Mosquitto )
pkg_search_module( MOSQUITTO REQUIRED libmosquitto )
if( NOT MOSQUITTO_FOUND )

	ExternalProject_Add( EXTERNAL_MQTT
		PREFIX ${CMAKE_SOURCE_DIR}/external/mosquitto
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

	ExternalProject_Add( EXTERNAL_XML
		PREFIX ${CMAKE_SOURCE_DIR}/external/tinyxml2
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

	ExternalProject_Add( EXTERNAL_JSON
		PREFIX ${CMAKE_SOURCE_DIR}/external/rapidjson
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
pkg_search_module( TINYFSM REQUIRED tinyfsm )
if( NOT TINYFSM_FOUND )

	ExternalProject_Add( EXTERNAL_FSM
		PREFIX ${CMAKE_SOURCE_DIR}/external/tinyfsm
		GIT_REPOSITORY https://github.com/digint/tinyfsm
	)

	ExternalProject_Add_Step( EXTERNAL_FSM refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

else()
	message( STATUS "TinyFsm already installed" )
endif()

find_program( GENERATOR generator )
if( NOT GENERATOR )

	message("Build Version Generator")
	ExternalProject_Add( EXTERNAL_VERSION
		PREFIX ${CMAKE_SOURCE_DIR}/external/version
		INSTALL_COMMAND ""
		GIT_REPOSITORY https://github.com/erichschroeter/cmake-auto-increment-build-number.git
	)

	add_executable( generator ${CMAKE_CURRENT_SOURCE_DIR}/version/src/generate.c )
else()
	message( STATUS "Version generator already installed" )
endif()

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
