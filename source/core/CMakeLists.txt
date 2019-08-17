add_subdirectory( designpatterns )
add_subdirectory( parameter )
add_subdirectory( xml )
#add_subdirectory( profiler )


add_library( core                       
                Generic.cpp 

                # Include the Design Patterns
                $<TARGET_OBJECTS:designpatterns>
            
                # Include others
                $<TARGET_OBJECTS:parameter> 

                # External Libraries
                $<TARGET_OBJECTS:xmlparser> 
)
                   
