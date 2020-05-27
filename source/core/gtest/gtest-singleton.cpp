// Inheritance
//#include "Generic.h"

// Design Pattern
#include "Singleton.h"

// Third-Party
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Beta
{
       public:
        std::string mName = "Beta";
};

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

class SingletonFeature : public ::testing::Test
{
       private:
       protected:
        virtual void TearDown()
        {
                if ( Singleton<Beta>::IsConstructed() )
                        Singleton<Beta>::Unregister();
        }
};

TEST_F( SingletonFeature, Construct )
{
        Beta &b1 = Singleton<Beta>::Instance();
        Beta &b2 = Singleton<Beta>::Instance();

        ASSERT_EQ( &b1, &b2 );
}

TEST_F( SingletonFeature, Validationg )
{
        ASSERT_EQ( Singleton<Beta>::IsConstructed(), false );

        Beta &b1 = Singleton<Beta>::Instance();

        ASSERT_EQ( Singleton<Beta>::IsConstructed(), true );
}

TEST_F( SingletonFeature, RegisterNewInstance )
{
        Beta *beta = new Beta();
        ASSERT_NO_THROW( Singleton<Beta>::Register( *beta ) );
}

TEST_F( SingletonFeature, RegisterExistingInstance )
{
        Beta &instance = Singleton<Beta>::Instance();
        Beta *beta = new Beta();

        ASSERT_ANY_THROW( Singleton<Beta>::Register( *beta ) );
}

TEST_F( SingletonFeature, UnregisterFailure )
{
        /*
	// Beta only exicst in scope
        {
                Beta beta;
                Singleton<Beta>::Register( beta );
        }

        // Beta does not excists but is registerd....
        ASSERT_ANY_THROW( Singleton<Beta>::Unregister() );
*/
}

int main( int argc, char **argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
