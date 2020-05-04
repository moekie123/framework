message( "Download External Dependencies" )
include(ExternalProject)

#Install the googletest framework
find_library( GTEST_LIB gtest )
find_library( GMOCK_LIB gmock )
if( NOT GTEST_LIB OR NOT GMOCK_LIB )

	ExternalProject_Add( googletest 
 		PREFIX ${CMAKE_SOURCE_DIR}/external/googletest
		GIT_REPOSITORY https://github.com/google/googletest
	)

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

else()
	message( STATUS "Mosquitto Library already installed" )
endif()

# Install the tinyxml library
find_library( XML_LIB tinyxml2 )
if( NOT XML_LIB )

	ExternalProject_Add( tinyxml 
		PREFIX ${CMAKE_SOURCE_DIR}/external/tinyxml2
		GIT_REPOSITORY  https://github.com/leethomason/tinyxml2.git
	)

else()
	message( STATUS "TinyXml2 Library already installed" )
endif()


