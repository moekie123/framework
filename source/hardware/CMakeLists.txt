add_subdirectory( drivers )
add_subdirectory( actuators )
add_subdirectory( sensors )

set( HARDWARE_SOURCES

	# Include hardware fundamentals
	${CMAKE_CURRENT_SOURCE_DIR}/Hardware.cpp

	# Include Driver Modules
        $<TARGET_OBJECTS:driver-chipset>
      	$<TARGET_OBJECTS:driver-device>
       	$<TARGET_OBJECTS:driver-signal>

      	# Include the controllers
      	$<TARGET_OBJECTS:actuators>
            
      	# Include the sensors
       	$<TARGET_OBJECTS:sensors>

)

set( FRAMEWORK_SOURCES
	${FRAMEWORK_SOURCES} 
	${HARDWARE_SOURCES}
	PARENT_SCOPE )

add_library( hardware ${HARDWARE_SOURCES} )
