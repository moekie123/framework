add_executable( gtest-configurator gtest-configurator.cpp )
target_link_libraries( gtest-configurator gtest gmock pthread core )
add_test( NAME configurator COMMAND gtest-configurator )

file( COPY gtest-configurator.xml DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

