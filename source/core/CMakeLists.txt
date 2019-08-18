add_subdirectory( designpatterns )
add_subdirectory( configurator )
add_subdirectory( parameter )

#add_subdirectory( profiler )


add_library( core                       
                Generic.cpp 

                # Include the Design Patterns
                $<TARGET_OBJECTS:designpatterns>
 
		# Include the Configurator
                $<TARGET_OBJECTS:configurator>
        
                # Include others
                $<TARGET_OBJECTS:parameter> 
)
                   
