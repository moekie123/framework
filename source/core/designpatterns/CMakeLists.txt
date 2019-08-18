# Creational Patterns
add_subdirectory( singleton )
add_subdirectory( factory )
add_subdirectory( builder )

# Structural Patterns
add_subdirectory( composite )

# Behavioural Patterns
add_subdirectory( observer )

add_library( designpatterns OBJECT

		singleton/Singleton.cpp
                factory/Factory.cpp
		builder/Builder.cpp

                composite/Composite.cpp 

                observer/Observer.cpp
            )

