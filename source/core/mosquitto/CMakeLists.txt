add_library( mqtt OBJECT
		Mosquitto.cpp
		)

add_executable( fsm-mqtt
			main.cpp 
			Mosquitto.cpp
			StateMachine.cpp )

target_link_libraries( fsm-mqtt core )

add_subdirectory( test )
