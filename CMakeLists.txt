cmake_minimum_required( VERSION 3.17.0 FATAL_ERROR )

Project( Framework LANGUAGES CXX C )

# Framework Version
set(VERSION_MAJOR   0)
set(VERSION_MINOR   4)
set(VERSION_PATCH   0)
set(VERSION_META "-alpha")

mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

message( STATUS "Project Name : ${CMAKE_PROJECT_NAME}" )

###############################################################################
###                          Verify the Hardware                            ###
###############################################################################

set( RPI_HARDWARE FALSE )

# Check if enviroment variables define the hardware
if( $ENV{HARDWARE} STREQUAL "RaspberryPi" )
	set( RPI_HARDWARE TRUE )
endif()

message( STATUS "Hardware [$ENV{HARDWARE}] recognized as embedded platform [${RPI_HARDWARE}]" )

###############################################################################
###                               Definitions                               ###
###############################################################################

#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/binary )

set( INSTALL_DIRECTORY /opt/framework/ )

###############################################################################
###                    Project Build Configuration                          ###
###############################################################################

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE )
endif()

message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )

###############################################################################
###                         Configure the Compiler                          ###
###############################################################################

include( CMakeDependentOption )

# Cross Compiling required when not running on RaspberryPi
cmake_dependent_option(
	CROSS_COMPILING "Build project for different platform" FALSE
	"RPI_HARDWARE"
	TRUE # RPI_HARDWARE true, apply this value
)

message( CHECK_START "Set required compiling method" )
if( ${CROSS_COMPILING} )
	message( CHECK_PASS "Crossing" )

	set( TOOLCHAIN aarch64-linux-gnu- )
	set( ARCHITECTURE arm64 )
	set( KERNEL kernel8 )

	set( CMAKE_C_COMPILER ${TOOLCHAIN}gcc )
	set( CMAKE_CXX_COMPILER ${TOOLCHAIN}g++ )
else()
	message( CHECK_PASS "Native" )

	# Find out the enviroment architecture
	set( TOOLCHAIN aarch64-linux-gnu- )
	set( ARCHITECTURE arm64 )
	set( KERNEL kernel8 )

	message( WARNING "CMake not ablel to dectect the architecture")
	return()

	set( CMAKE_CXX_COMPILER g++ )
endif()

# Terminate build if C++ compiler is missing
message( CHECK_START "Check for C++ compiler" )
if( CMAKE_CXX_COMPILER_LOADED )
	message( CHECK_PASS "Loaded" )

	message( STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
	message( STATUS "C++ compiler id: ${CMAKE_CXX_COMPILER_ID}")
	message( STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

	set( CMAKE_CXX_STANDARD 17 )
	set( CMAKE_CXX_STANDARD_REQUIRED ON )
	message( STATUS "C++ standard: ${CMAKE_CXX_STANDARD}" )
	
#	set( CMAKE_CXX_EXTENSIONS OFF )
else()
	message( CHECK_FAIL "Not loaded" )
	return()
endif()

# Configure the compiler flags
set( COMPILER_FLAGS )
list( APPEND COMPILER_FLAGS "-Wall" "-Wno-psabii" "-v" "-time")

if( ${CMAKE_BUILD_TYPE} STREQUAL "Release" )
	list(APPEND COMPILER_FLAGS "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")

elseif( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
	list(APPEND COMPILER_FLAGS "-O3" "-g3" "-Wno-unused")

endif()
message( STATUS "Compile flags: " ${COMPILER_FLAGS} )

add_compile_options( ${COMPILER_FLAGS} )

###############################################################################
###                           COMPILER ANALYTICS                            ###
###############################################################################

#set_property( GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time" )

###############################################################################
###                         Configure Coding Tools                          ###
###############################################################################

# Setup CppCheck
#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

#if (CMAKE_CXX_CPPCHECK)
#	list(
#		APPEND CMAKE_CXX_CPPCHECK 
#			"--enable=warning"
#			"--inconclusive"
#			"--force" 
#			"--inline-suppr"
#			"--language=c++"
#			"--suppress=*:*external*"
#    	)
#endif()

# Setup CTags

#set_source_files_properties( tags PROPERTIES GENERATED true )

#add_custom_target ( tags ALL
#	COMMAND ctags -f tags -R --c++-kinds=+p --fields=+iaS ${CMAKE_CURRENT_SOURCE_DIR} --exclude=${CMAKE_SOURCE_DIR}/external/*
#   	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )


###############################################################################
###                             Build Kernel                                ###
###############################################################################

# Define the sysroot path for the RaspberryPi Kernel
set( CMAKE_SYSROOT "${CMAKE_SOURCE_DIR}/kernel/linux" )

set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )

set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )

message( STATUS "Additional Kernel Compile flags: " ${COMPILER_FLAGS} )

add_subdirectory( kernel )

###############################################################################
###                       Download External Projects                        ###
###############################################################################
add_subdirectory( external )

# List of header file directories
set( HEADER_DIRECTORIES )
list( APPEND HEADER_DIRECTORIES ${CMAKE_SOURCE_DIR}/include )
list( APPEND HEADER_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/output/include )
list( APPEND HEADER_DIRECTORIES ${CMAKE_SOURCE_DIR}/kernel/include )

include_directories( ${HEADER_DIRECTORIES} )

set( LIBRARY_DIRECTORIES )
list( APPEND LIBRARY_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/output/lib )

link_directories( ${LIBRARY_DIRECTORIES} )

#find_library( EXTERNAL_LIBRARIES 
#	NAMES mosquitto
#	NO_DEFAULT_PATH	
#	PATHS ${CMAKE_SOURCE_DIR}/external/output/lib
#	NO_CMAKE_FIND_ROOT_PATH
#	REQUIRED)
#message( "#########" ${EXTERNAL_LIBRARIES} )

###############################################################################
###                      Configure Test Enviroment                          ###
###############################################################################

# Build Test Enviroment
message( "Configure Test Enviroment" )
function( gsetup gtest-name )

	message("Setup [gtest-${gtest-name}] target")

	add_executable( gtest-${gtest-name} gtest-${gtest-name}.cpp )

	target_link_libraries( gtest-${gtest-name} TEST_LIBRARIES )

	target_compile_options( gtest-${gtest-name} PRIVATE ${COMPILER_FLAGS}  )
	target_include_directories( gtest-${gtest-name} PRIVATE ${HEADER_DIRECTORIES} )

	add_test( NAME ${gtest-name} COMMAND gtest-${gtest-name} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
	install( TARGETS gtest-${gtest-name} DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )

endfunction()
include( CTest )

###############################################################################
###                           Build the Framework                           ###
###############################################################################

add_subdirectory( prototype )
return()

add_subdirectory( source )

return()


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
