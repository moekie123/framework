add_executable( gtest-parameter gtest-parameter.cpp )
target_link_libraries( gtest-parameter gtest gmock pthread core tinyxml2 )
add_test( NAME parameter COMMAND gtest-parameter WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

#add_executable( gtest-parameter-range gtest-parameter-range.cpp )
#target_link_libraries( gtest-parameter-range gtest gmock pthread core )
#add_test( NAME parameter-range COMMAND gtest-parameter-range )
