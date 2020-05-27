# Object Unit Tests
gsetup( object )
target_link_libraries( gtest-object generic )

# Generic Unit Test
gsetup( generic )
target_link_libraries( gtest-generic generic )

# Factory Unit Tests
gsetup( factory )
target_link_libraries( gtest-factory generic )

# Singleton Unit Tests
gsetup( singleton )
target_link_libraries( gtest-singleton generic )

# Builder Unit Tests
gsetup( builder )
target_link_libraries( gtest-builder generic )

# Composite Unit Tests
gsetup( composite )
target_link_libraries( gtest-composite generic )

# Observer Unit Tests
gsetup( observer )
target_link_libraries( gtest-observer generic )

# Statemachine Unit Tests
gsetup( statemachine )
target_link_libraries( gtest-statemachine generic )
