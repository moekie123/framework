# Creational Patterns
add_subdirectory( singleton )
add_subdirectory( factory )

# Structural Patterns
add_subdirectory( composite )

# Behavioural Patterns
add_subdirectory( observer )

add_library( designpatterns OBJECT
                singleton/Singleton.cpp
                factory/AbstractFactory.cpp
                                              
                composite/Composite.cpp 

                observer/Observer.cpp
            )

