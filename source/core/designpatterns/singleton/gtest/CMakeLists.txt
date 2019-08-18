add_executable( gtest-singleton gtest-singleton.cpp )
target_link_libraries( gtest-singleton gtest core )
add_test( NAME singlton COMMAND gtest-singleton )
