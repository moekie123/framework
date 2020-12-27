add_library( configurator OBJECT
		Configurator.cpp
		)

target_include_directories( configurator PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( configurator PRIVATE ${COMPILER_FLAGS}  )

add_subdirectory( test )

