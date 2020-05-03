# Factory Unit Tests
add_executable( gtest-factory gtest-factory.cpp )
target_link_libraries( gtest-factory gtest pthread core tinyxml2 )
add_test( NAME factory COMMAND gtest-factory WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

# Singleon Unit Tests
add_executable( gtest-singleton gtest-singleton.cpp )
target_link_libraries( gtest-singleton gtest pthread core tinyxml2 )
add_test( NAME singlton COMMAND gtest-singleton WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

# Builder Unit Tests
add_executable( gtest-builder gtest-builder.cpp )
target_link_libraries( gtest-builder gtest gmock pthread core tinyxml2 )
add_test( NAME builder COMMAND gtest-builder WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

# Composite Unit Tests
add_executable( gtest-composite gtest-composite.cpp )
target_link_libraries( gtest-composite gtest gmock pthread core tinyxml2 )
add_test( NAME composite COMMAND gtest-composite WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )

# Observer Unit Tests
add_executable( gtest-observer gtest-observer.cpp ) 
target_link_libraries( gtest-observer gtest gmock pthread core tinyxml2 )
add_test( NAME observer COMMAND gtest-observer WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
