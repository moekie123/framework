add_subdirectory( core )
add_subdirectory( hardware )

Project( Framework )
add_executable( Framework main.cpp Framework.cpp )
target_link_libraries( Framework PRIVATE 
					core
					hardware
			)
