add_library( actuators OBJECT
                Actuator.cpp )

add_executable( fsm-actuator
			main.cpp 
			Actuator.cpp )

target_link_libraries( fsm-actuator Framework 
				    mosquitto
				    stdc++fs 
				    tinyxml2 )

add_subdirectory( test )
