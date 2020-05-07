add_executable( gtest-actuator gtest-actuator.cpp )
target_link_libraries( gtest-actuator gtest pthread actuators core tinyxml2 )


install( TARGETS gtest-actuator DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )
