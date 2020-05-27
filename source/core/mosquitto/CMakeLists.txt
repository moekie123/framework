add_library( mqtt OBJECT
		Mosquitto.cpp
		)

add_executable( fsm-mqtt
			main.cpp 
			Mosquitto.cpp )

target_link_libraries( fsm-mqtt Framework 
				mosquitto 
				tinyxml2 )

add_subdirectory( test )
