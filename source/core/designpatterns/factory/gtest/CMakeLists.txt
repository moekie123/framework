add_executable( gtest-abstract-factory gtest-abstract-factory.cpp )
target_link_libraries( gtest-abstract-factory gtest core )
add_test( NAME factory-abstract COMMAND gtest-abstract-factory )
