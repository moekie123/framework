add_library( parameter OBJECT
                ParameterFactory.cpp
                Parameter.cpp 
                ParameterRange.cpp)

add_subdirectory( test )
