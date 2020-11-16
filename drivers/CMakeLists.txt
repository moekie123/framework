
# Install drivers
if( $RPI_HARDWARE )

	add_custom_target( driver ALL 
				COMMENT "Build driver(s)"
				COMMAND make all
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

	add_custom_target( kernel_module 
				COMMENT "Install Kernel Modules(s)" 
				COMMAND make install
				WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

endif()

