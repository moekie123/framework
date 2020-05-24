# Object Unit Tests
gsetup( object )
target_link_libraries( gtest-object core)

# Generic Unit Test
gsetup( generic )
target_link_libraries( gtest-generic core)

# Factory Unit Tests
gsetup( factory )
target_link_libraries( gtest-factory core)

# Singleton Unit Tests
gsetup( singleton )
target_link_libraries( gtest-singleton core)

# Builder Unit Tests
gsetup( builder )
target_link_libraries( gtest-builder core)

# Composite Unit Tests
gsetup( composite )
target_link_libraries( gtest-composite core)

# Observer Unit Tests
gsetup( observer )
target_link_libraries( gtest-observer core)
