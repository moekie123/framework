add_executable( gtest-actuator gtest-actuator.cpp )

target_link_libraries( gtest-actuator gtest actuators core )
