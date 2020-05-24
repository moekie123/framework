# Collect Framework sources
set( FRAMEWORK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Framework.cpp )

# The following directories will extend FRAMEWORK_SOURCES
add_subdirectory( core )
add_subdirectory( hardware )

# Merge to one library
add_library( Framework ${FRAMEWORK_SOURCES} )
