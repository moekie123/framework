add_subdirectory( drivers )
add_subdirectory( actuators )
add_subdirectory( sensors )

add_library( hardware                
                Hardware.cpp

                # Include Driver Modules
                $<TARGET_OBJECTS:driver-chipset>
                $<TARGET_OBJECTS:driver-device>
                $<TARGET_OBJECTS:driver-signal>

                # Include the controllers
                $<TARGET_OBJECTS:actuators>
            
                # Include the sensors
                $<TARGET_OBJECTS:sensors>
           )
