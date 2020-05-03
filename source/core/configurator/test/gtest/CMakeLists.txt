add_executable( gtest-configurator gtest-configurator.cpp )

target_link_libraries( gtest-configurator gtest gmock pthread core )

add_test( NAME configurator COMMAND gtest-configurator WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

file( COPY gtest-configurator.xml DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

