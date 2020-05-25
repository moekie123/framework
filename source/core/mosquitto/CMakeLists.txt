add_library( mqtt OBJECT
		Mosquitto.cpp
		StateMachine.cpp
		Visitor.cpp
		)

add_executable( fsm-mqtt
			main.cpp 
			Mosquitto.cpp
			StateMachine.cpp )

target_link_libraries( fsm-mqtt Framework mosquitto tinyxml2 )

add_subdirectory( test )
