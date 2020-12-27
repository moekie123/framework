add_library( parameter OBJECT
                Parameter.cpp 
		#ParameterRange.cpp
		)

target_include_directories( parameter PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( parameter PRIVATE ${COMPILER_FLAGS}  )

add_subdirectory( test )
