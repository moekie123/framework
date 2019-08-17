add_executable( gtest-chipset gtest-chipset.cpp )
target_link_libraries( gtest-chipset gtest hardware core )

file( COPY gtest-pwmchipset0 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
