cmake_minimum_required( VERSION 3.13.0 )

message( "Building Framework" )
Project( Framework )

# Framework Version
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   2   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
set(VERSION_META "-alpha")

mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)
message( "Version " ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} )

# Setup Enviroment
message( "Configure Compiler" )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binairy )

# Include external dependencies
add_subdirectory( external )

# Setup CTags
message( "Configure CTags" )
set_source_files_properties( tags PROPERTIES GENERATED true)
add_custom_command ( OUTPUT tags ALL
	COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extras=+q .    
    	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )

# Validate Source
message( "Check source code" )
set(CMAKE_CXX_CPPCHECK "cppcheck")

# Build Test Enviroment
message( "Configure Test Enviroment" )
include( CTest )

# Build Enviroment
message( "Setup the directory tree" )
include_directories( include )
add_subdirectory( source )

message( "Configure Cucumber Enviroment" )
add_subdirectory( features )

# Build Project
message( "Building Framework" )

add_executable( Framework 
			main.cpp 
			source/Framework.cpp )

target_link_libraries( Framework PUBLIC
				core
				hardware 
				tinyxml2
			      	mosquitto )

add_dependencies( Framework
			version )


# Documentation
message( "Configure Documentation" )
add_subdirectory( documentation )
