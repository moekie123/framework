# first we can indicate the documentation build as an option and set it to ON by default
option( BUILD_DOC "Build documentation" OFF )

# check if Doxygen is installed
find_package( Doxygen )

if ( DOXYGEN_FOUND )
	# set input and output files
	set( DOXYGEN_LAYOUT ${CMAKE_SOURCE_DIR}/documentation/DoxygenLayout.xml  )

	set( DOXYGEN_IN  ${CMAKE_SOURCE_DIR}/documentation/Doxyfile.in )
    	set( DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile ) 

    	# request to configure the file
    	configure_file( ${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY )
    	
	message( "Doxygen build started" )
	
	# note the option ALL which allows to build the docs together with the application
	add_custom_target( doc_verify ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        	COMMENT "Verify documentation for Doxygen"
        	VERBATIM )

	add_custom_target( doc_install
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
		COMMAND cp -r ${CMAKE_CURRENT_BINARY_DIR}/html /var/www 
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Install documentation for Doxygen"
	       	VERBATIM )

	install( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION /var/www )
 
else ( DOXYGEN_FOUND )
	message( "Doxygen need to be installed to generate the doxygen documentation" )
endif ( DOXYGEN_FOUND )
