add_executable( gtest-parameter gtest-parameter.cpp )
target_link_libraries( gtest-parameter gtest gmock pthread core )
add_test( NAME parameter COMMAND gtest-parameter )

#add_executable( gtest-parameter-range gtest-parameter-range.cpp )
#target_link_libraries( gtest-parameter-range gtest gmock pthread core )
#add_test( NAME parameter-range COMMAND gtest-parameter-range )

add_executable( gtest-parameter-factory gtest-parameter-factory.cpp )
target_link_libraries( gtest-parameter-factory gtest gmock pthread core )
add_test( NAME parameter-factory COMMAND gtest-parameter-factory )

