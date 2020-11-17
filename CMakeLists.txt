cmake_minimum_required( VERSION 3.17.0 )

Project( Framework )

# Framework Version
set(VERSION_MAJOR   0)
set(VERSION_MINOR   4)
set(VERSION_PATCH   0)
set(VERSION_META "-alpha")

mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

###############################################################################
###                          Verify the Hardware                            ###
###############################################################################
set( RPI_HARDWARE FALSE )
set( CROSS_COMPILING FALSE )

if( $ENV{HARDWARE} STREQUAL "RaspberryPi" )
	set( RPI_HARDWARE TRUE )
endif()

if( $RPI_HARDWARE )
        message( STATUS "Project Build as Raspberry Pi Project" )
else()
        message( STATUS "Project Build as Cross Compiler Project" )
	set( CROSS_COMPILING TRUE )
endif()

###############################################################################
###                         Configure the Compiler                          ###
###############################################################################
message("Configure Compiler")
 
# Define the (Cross) Compiler
if( $CROSS_COMPILING )
	message( STATUS "Configure CrossCompiler" )

        # Define the sysroot path for the RaspberryPi distribution in our tools folder
#        set( CMAKE_FIND_ROOT_PATH /root/framework/kernel/linux )

        # Use our definitions for compiler tools
        set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )

        # Search for libraries and headers in the target directories only
        set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
        set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

	set( CMAKE_CXX_FLAGS "-Wall -g3 -Wno-psabii -I/usr/local/include" )
	set( LDFLAGS -L/usr/local/lib )

	set( CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++ )
else()
	set( CMAKE_CXX_COMPILER g++ )
endif()

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS ON )

set ( CMAKE_CXX_STANDARD 17 )

add_definitions(-Wall -g3 -Wno-psabii ) 

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binary )
set( CMAKE_INSTALL_OUTPUT_DIRECTORY /opt/framework/ )

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

###############################################################################
###                       Download External Projects                        ###
###############################################################################
add_subdirectory( external )

return()

###############################################################################
###                         Configure Coding Tools                          ###
###############################################################################

# Validate Source
message( "Check source code" )
#set(CMAKE_CXX_CPPCHECK "cppcheck")

# Setup CTags
message( "Configure CTags" )
set_source_files_properties( tags PROPERTIES GENERATED true)
add_custom_target ( tags ALL
	COMMAND ctags -f tags -R --c++-kinds=+p --fields=+iaS --extras=+q ${CMAKE_CURRENT_SOURCE_DIR} 
    	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

###############################################################################
###                      Configure Test Enviroment                          ###
###############################################################################

# Build Test Enviroment
message( "Configure Test Enviroment" )
function( gsetup gtest-name )
	message("Setup [gtest-${gtest-name}] target")
	add_executable( gtest-${gtest-name} gtest-${gtest-name}.cpp )
	target_link_libraries( gtest-${gtest-name} gtest gmock pthread )
	add_test( NAME ${gtest-name} COMMAND gtest-${gtest-name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	install( TARGETS gtest-${gtest-name} DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )
endfunction()
include( CTest )

###############################################################################
###                           Build the Framework                           ###
###############################################################################

# Build Enviroment
message( "Setup the directory tree" )
include_directories( include )
add_subdirectory( source )
add_subdirectory( prototype )

# Include drivers
add_subdirectory( drivers )

###############################################################################
###                         Build Behaviour Test                            ###
###############################################################################

message( "Configure Cucumber Enviroment" )
add_subdirectory( features )

###############################################################################
###                         Build Application                               ###
###############################################################################

message( "Building Application" )

# Collect Framework sources
add_executable( Application main.cpp )

add_custom_command( TARGET Application
			COMMAND echo "Build Framework [${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}${VERSION_META}]"
			PRE_BUILD)
	
target_link_libraries( Application PUBLIC 	Framework	
					  	tinyxml2
				      	  	mosquitto )

add_dependencies( Application version )

install( TARGETS Application DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY} )

###############################################################################
###                         Generate Documentation                          ###
###############################################################################
message( "Configure Documentation" )
add_subdirectory( documentation )
