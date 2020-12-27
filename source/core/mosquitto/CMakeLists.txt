add_library( mqtt OBJECT
		Mosquitto.cpp
		StateMachine.cpp
		Visitor.cpp
		)

target_include_directories( mqtt PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( mqtt PRIVATE ${COMPILER_FLAGS}  )

add_executable( fsm-mqtt
			main.cpp 
			../../Framework.cpp
			Mosquitto.cpp
			StateMachine.cpp )

target_link_libraries( fsm-mqtt Framework 
				mosquitto 
				tinyxml2 )

add_subdirectory( test )
