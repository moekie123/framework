add_subdirectory( configurator )
add_subdirectory( parameter )

add_subdirectory( utils )

add_subdirectory( gtest )

add_library( core                       
                Generic.cpp 

		# Creational Desing Patterns
		Singleton.cpp
       	       	Factory.cpp
		Builder.cpp
		
		# Structural Design Patterns
	        Composite.cpp 
		
		# Behavioural Design Patterns
	       	Observer.cpp

		# Include the Configurator
                $<TARGET_OBJECTS:configurator>
        
                # Include others
                $<TARGET_OBJECTS:parameter> 
)
