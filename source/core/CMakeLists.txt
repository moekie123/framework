add_subdirectory( configurator )
add_subdirectory( parameter )
add_subdirectory( mosquitto )
add_subdirectory( gtest )

add_library( fundamentals OBJECT
		# Include Core Fundamentals	
		${CMAKE_CURRENT_SOURCE_DIR}/Object.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Generic.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Singleton.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Factory.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Builder.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/Composite.cpp 
		${CMAKE_CURRENT_SOURCE_DIR}/Observer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Subject.cpp )

# Collect Framework sources
set( CORE_SOURCES
	# Include the Fundamentals
        $<TARGET_OBJECTS:fundamentals>

	# Include the Configurator
        $<TARGET_OBJECTS:configurator>
        
	# Include others
      	$<TARGET_OBJECTS:parameter> 

	# Include the Configurator
        $<TARGET_OBJECTS:mqtt>
)

# Extend Framework Sources
set( FRAMEWORK_SOURCES
	${FRAMEWORK_SOURCES} 
	${CORE_SOURCES}
	PARENT_SCOPE )

# Create private core-Library
add_library( core ${CORE_SOURCES} )
