# Build step defenition
add_executable( step_definition step_definitions/step_definitions.cpp ) 

# Link the executable
target_link_libraries( step_definition gtest gmock pthread framework cucumber-cpp tinyxml2 )

# Cucumber requires first the steps running 
add_custom_target( cucumber 
	WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" 

	# Running step definition 
	COMMAND echo "setup step definitions"
       	COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/step_definition &

	# Start the actual test enivoment
	COMMAND echo "start cucumber enviroment"
	COMMAND cucumber .
	)
