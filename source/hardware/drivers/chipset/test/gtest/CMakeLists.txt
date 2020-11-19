gsetup( chipset )
target_link_libraries( gtest-chipset generic hardware )

file( COPY gtest-pwmchipset0 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
