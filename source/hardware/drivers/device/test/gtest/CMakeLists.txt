add_executable( gtest-device gtest-device.cpp )
target_link_libraries( gtest-device gtest gmock pthread hardware core )

file( COPY gtest-pwmchipset0 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
