add_executable( gtest-configurator gtest-configurator.cpp )

target_link_libraries( gtest-configurator gtest gmock pthread core tinyxml2 )

add_test( NAME configurator COMMAND gtest-configurator WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
file( COPY gtest-configurator.xml DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

install( TARGETS gtest-configurator DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )
install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/gtest-configurator.xml DESTINATION ${CMAKE_INSTALL_OUTPUT_DIRECTORY}/gtest )

