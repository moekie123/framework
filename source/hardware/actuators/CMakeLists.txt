add_library( actuators OBJECT
                Actuator.cpp )

target_include_directories( actuators PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( actuators PRIVATE ${COMPILER_FLAGS}  )

add_subdirectory( test )
