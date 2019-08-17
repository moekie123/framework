cmake_minimum_required( VERSION 3.0.0 )

include( CTest )

# Setup Enviroment
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binairy )

# Build Enviroment
include_directories( include )

add_subdirectory( source )

add_subdirectory( documentation )
