# Device Unit Tests
gsetup( device )
target_link_libraries( gtest-device generic hardware )

file( COPY gtest-pwmchipset0 DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
