add_executable( gtest-observer gtest-observer.cpp )
target_link_libraries( gtest-observer gtest gmock pthread core )
add_test( NAME observer COMMAND gtest-observer )
