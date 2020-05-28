// Inheritance
#include "../../Mosquitto.h"

// Interfaces
#include "IMosquitto.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"
#include "StateMachine.h"

// Testing
#include "mocks/MockConfigurator.h"
#include "mocks/MockMosquitto.h"
#include "mocks/MockParameter.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "tinyfsm.hpp"

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;
using ::testing::Return;

class MosquittoFeature : public ::testing::Test
{
       private:
       protected:
        NiceMock<MockConfigurator> mConfig;

        virtual ~MosquittoFeature() {}

        virtual void SetUp()
        {
                if ( !Singleton<MockConfigurator>::IsConstructed() )
                {
                        mConfig.stringResults["hostname"] = "localhost";
                        EXPECT_CALL( mConfig, GetString( "Mosquitto", "client", "hostname", testing::_ ) ).WillRepeatedly( testing::Return( true ) );

                        mConfig.stringResults["port"] = "1833";
                        EXPECT_CALL( mConfig, GetString( "Mosquitto", "client", "port", testing::_ ) ).WillRepeatedly( testing::Return( true ) );

                        mConfig.stringResults["username"] = "rsalm";
                        EXPECT_CALL( mConfig, GetString( "Mosquitto", "client", "username", testing::_ ) ).WillRepeatedly( testing::Return( true ) );

                        mConfig.stringResults["password"] = "rsalm";
                        EXPECT_CALL( mConfig, GetString( "Mosquitto", "client", "password", testing::_ ) ).WillRepeatedly( testing::Return( true ) );

                        Singleton<MockConfigurator>::Register( mConfig );
                }

                if ( !Singleton<Factories>::IsConstructed() )
                {
                        Factories* factory = new Factories();
                        factory->Register<IConfigurator>( "Configurator", &MockConfigurator::builder );
 	                Singleton<Factories>::Register( *factory );
               }
        }
};

/**
 * GTest: Construct the client
 */
TEST_F( MosquittoFeature, Default )
{
        Mosquitto* mosquitto = new Mosquitto( mConfig );
        ASSERT_NE( mosquitto, nullptr );
}

TEST_F( MosquittoFeature, Interface )
{
        IMosquitto* mosquitto = new Mosquitto( mConfig );
        ASSERT_NE( mosquitto, nullptr );
}

TEST_F( MosquittoFeature, Builder )
{
        auto mosquitto = Mosquitto::builder.Build( &mConfig, "Mosquitto" );
        ASSERT_EQ( typeid( IMosquitto* ), typeid( mosquitto ) );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
