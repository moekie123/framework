add_library( driver-device OBJECT
                Device.cpp 
                )

target_include_directories( driver-device PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( driver-device PRIVATE ${COMPILER_FLAGS}  )

add_subdirectory( test )
