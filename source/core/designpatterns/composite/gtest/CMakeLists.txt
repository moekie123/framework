add_executable( gtest-composite gtest-composite.cpp )
target_link_libraries( gtest-composite gtest core )
add_test( NAME composite COMMAND gtest-composite )
