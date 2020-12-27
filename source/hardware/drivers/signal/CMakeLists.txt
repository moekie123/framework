add_library( driver-signal OBJECT
		Signal.cpp)

target_include_directories( driver-signal PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( driver-signal PRIVATE ${COMPILER_FLAGS}  )

# add_subdirectory( test )
