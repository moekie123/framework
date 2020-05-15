# Mosquitto Unit Tests
gsetup( mosquitto )
target_link_libraries( 	gtest-mosquitto 
			core
			tinyxml2
			mosquitto			
			)

#add_executable( gtest-mosquitto gtest-mosquitto.cpp )
#target_link_libraries( gtest-mosquitto gtest gmock pthread core tinyxml2 mosquitto )
#add_test( NAME mosquitto COMMAND gtest-mosquitto WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

