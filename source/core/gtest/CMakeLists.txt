# Object Unit Tests
gsetup( object )
target_link_libraries( gtest-object fundamentals )

# Generic Unit Test
gsetup( generic )
target_link_libraries( gtest-generic fundamentals )

# Factory Unit Tests
gsetup( factory )
target_link_libraries( gtest-factory fundamentals )

# Singleton Unit Tests
gsetup( singleton )
target_link_libraries( gtest-singleton fundamentals )

# Builder Unit Tests
gsetup( builder )
target_link_libraries( gtest-builder fundamentals )

# Composite Unit Tests
gsetup( composite )
target_link_libraries( gtest-composite fundamentals )

# Observer Unit Tests
gsetup( observer )
target_link_libraries( gtest-observer fundamentals )
