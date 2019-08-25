# Factory Unit Tests
add_executable( gtest-factory gtest-factory.cpp )
target_link_libraries( gtest-factory gtest core )
add_test( NAME factory COMMAND gtest-factory )

# Singleon Unit Tests
add_executable( gtest-singleton gtest-singleton.cpp )
target_link_libraries( gtest-singleton gtest core )
add_test( NAME singlton COMMAND gtest-singleton )

# Builder Unit Tests
add_executable( gtest-builder gtest-builder.cpp )
target_link_libraries( gtest-builder gtest core )
add_test( NAME builder COMMAND gtest-builder )

# Composite Unit Tests
add_executable( gtest-composite gtest-composite.cpp )
target_link_libraries( gtest-composite gtest core )
add_test( NAME composite COMMAND gtest-composite )

# Observer Unit Tests
add_executable( gtest-observer gtest-observer.cpp )
target_link_libraries( gtest-observer gtest gmock pthread core )
add_test( NAME observer COMMAND gtest-observer )
