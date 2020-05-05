# Collect Framework sources
set( FRAMEWORK_SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/Framework.cpp )

add_subdirectory( core )
add_subdirectory( hardware )

add_library( framework 
		${FRAMEWORK_SOURCES} 
		)
