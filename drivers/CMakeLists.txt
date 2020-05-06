
# Install drivers

add_custom_target( build_drivers ALL 
			COMMENT "Build driver(s)"
			COMMAND make all
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
