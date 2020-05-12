cmake_minimum_required( VERSION 3.13.0 )

Project( Framework )

# Framework Version
set(VERSION_MAJOR   0)
set(VERSION_MINOR   2)
set(VERSION_PATCH   0)
set(VERSION_META "-alpha")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

# Setup Enviroment
message( "Configure Compiler" )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binairy )
set( CMAKE_INSTALL_OUTPUT_DIRECTORY /opt/framework/ )

# Include external dependencies
set( ALL_EXTERNALS_BUILD OFF )
add_subdirectory( external )
if( NOT ${ALL_EXTERNALS_BUILD} )
	message( AUTHOR_WARNING "Externals are not ready yet, try again..." )
	return()
endif()

# Setup CTags
message( "Configure CTags" )
set_source_files_properties( tags PROPERTIES GENERATED true)
add_custom_command ( OUTPUT tags ALL
	COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extras=+q .    
    	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )

# Build Test Enviroment
message( "Configure Test Enviroment" )
function( gsetup gtest-name )
	message("Setup [gtest-${gtest-name}] target")
	add_executable( gtest-${gtest-name} gtest-${gtest-name}.cpp )
	add_dependencies( gtest-${gtest-name} ext-gtest )
	target_link_libraries( gtest-${gtest-name} gtest gmock pthread )
	add_test( NAME ${gtest-name} COMMAND gtest-${gtest-name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	install( TARGETS gtest-${gtest-name} DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )
endfunction()
include( CTest )

# Validate Source
message( "Check source code" )
set(CMAKE_CXX_CPPCHECK "cppcheck")

# Build Enviroment
message( "Setup the directory tree" )
include_directories( include )
add_subdirectory( source )
add_subdirectory( prototype )

# Include drivers
add_subdirectory( drivers )

message( "Configure Cucumber Enviroment" )
add_subdirectory( features )

# Build Project
message( "Building Framework" )

# Collect Framework sources

add_executable( Framework main.cpp )
add_custom_command( TARGET Framework 
	COMMAND echo "Build Framework [${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${VERSION_META}]"
	PRE_BUILD)
	
target_link_libraries( Framework PUBLIC
				framework
				tinyxml2
			      	mosquitto )

add_dependencies( Framework version )

install( TARGETS Framework DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY} )

# Documentation
message( "Configure Documentation" )
add_subdirectory( documentation )
