message( "Download External Dependencies" )
include(ExternalProject)

#Install the googletest framework
find_library( GTEST_LIB gtest )
find_library( GMOCK_LIB gmock )
if( NOT GTEST_LIB OR NOT GMOCK_LIB )

	ExternalProject_Add( googletest 
		PREFIX ${CMAKE_SOURCE_DIR}/external/googletest
		CMAKE_ARGS "-DBUILD_SHARED_LIBS=ON"
		GIT_REPOSITORY https://github.com/google/googletest
	)

	ExternalProject_Add_Step( googletest refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

else()
	message( STATUS "Google Test Library already installed" )
endif()

# Install the mosquitto library
find_library( MQTT_LIB mosquitto )
if( NOT MQTT_LIB )

	ExternalProject_Add( mqtt
		PREFIX ${CMAKE_SOURCE_DIR}/external/mqtt
		CMAKE_ARGS "-DDOCUMENTATION=OFF"
		GIT_REPOSITORY  https://github.com/eclipse/mosquitto.git
	)

	ExternalProject_Add_Step( mqtt refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

else()
	message( STATUS "Mosquitto Library already installed" )
endif()

# Install the tinyxml library
find_library( XML_LIB tinyxml2 )
if( XML_LIB )

	ExternalProject_Add( tinyxml 
		PREFIX ${CMAKE_SOURCE_DIR}/external/tinyxml2
		GIT_REPOSITORY  https://github.com/leethomason/tinyxml2.git
	)

	ExternalProject_Add_Step( tinyxml refresh
		ALWAYS TRUE
		DEPENDEES "install"
		COMMENT "refresh shared library cache" 
		COMMAND ldconfig )

else()
	message( STATUS "TinyXml2 Library already installed" )
endif()


