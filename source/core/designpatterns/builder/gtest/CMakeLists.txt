add_executable( gtest-builder gtest-builder.cpp )
target_link_libraries( gtest-builder gtest core )
add_test( NAME builder COMMAND gtest-builder )
