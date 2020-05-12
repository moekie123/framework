add_library( mqtt OBJECT
		Mosquitto.cpp
		)

add_executable( MqttFSM
			main.cpp 
			MqttStateMachine.cpp )

#target_link_libraries( MqttFSM tinyfsm )

add_subdirectory( test )
