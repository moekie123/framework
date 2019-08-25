cmake_minimum_required( VERSION 3.0.0 )

Project( SpyderFramework )

set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   1   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# Setup Enviroment
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binairy )

# Setup CTags
set_source_files_properties( tags PROPERTIES GENERATED true)
add_custom_command ( OUTPUT tags
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extras=+q . 
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )

# Build Test Enviroment
include( CTest )

# Build Enviroment
include_directories( include )
add_subdirectory( source )

# Build Project
add_executable( Framework main.cpp source/Framework.cpp tags )

target_link_libraries( Framework PUBLIC
				core
				hardware )
# Documentation
add_subdirectory( documentation )
