add_executable( gtest-factory gtest-factory.cpp )
target_link_libraries( gtest-factory gtest core )
add_test( NAME factory COMMAND gtest-factory )
