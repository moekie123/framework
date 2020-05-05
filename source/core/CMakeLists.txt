add_subdirectory( configurator )
add_subdirectory( parameter )

add_subdirectory( utils )

add_subdirectory( mosquitto )

add_subdirectory( gtest )

# Collect Framework sources

set( CORE_SOURCES

	# Include Core Fundamentals	
	${CMAKE_CURRENT_SOURCE_DIR}/Generic.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Singleton.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Factory.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Builder.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Composite.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/Observer.cpp
	
	# Include the Configurator
        $<TARGET_OBJECTS:configurator>
        
	# Include others
      	$<TARGET_OBJECTS:parameter> 
)

set( FRAMEWORK_SOURCES
	${FRAMEWORK_SOURCES} 
	${CORE_SOURCES}
	PARENT_SCOPE )

add_library( core ${CORE_SOURCES} )
