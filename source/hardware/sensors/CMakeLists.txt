add_library( sensors OBJECT
                Sensor.cpp )

target_include_directories( sensors PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( sensors PRIVATE ${COMPILER_FLAGS}  )

#add_subdirectory( test )

