add_library( driver-chipset OBJECT
                Chipset.cpp 
                )

target_include_directories( driver-chipset PRIVATE ${HEADER_DIRECTORIES} )
target_compile_options( driver-chipset PRIVATE ${COMPILER_FLAGS}  )

add_subdirectory( test )
