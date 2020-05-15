#include "../../Mosquitto.h"
#include "IMosquitto.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Singleton.h"
#include "Factory.h"

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

class ConstructFeature: 
	public ::testing::Test 
{
	private:

	protected:
		NiceMock< MockConfigurator > mConfig;

    	virtual ~ConstructFeature() {}

    	virtual void SetUp() 
	{
		mConfig.stringResults["hostname"] = "localhost";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "hostname", testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["port"]     = "1833";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "port", testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["username"] = "rsalm";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "username"  , testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["password"] = "rsalm";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "password"  , testing::_ )).WillRepeatedly( testing::Return( true ));

		Singleton< MockConfigurator >::Register( mConfig );

		Factory& factory = Singleton< Factory >::Instance();

		factory.Register< MockConfigurator >( "Configurator" );
	}
};

/**
 * GTest: Construct the client
 */
TEST_F( ConstructFeature, Default )
{
	Mosquitto* mosquitto = new Mosquitto( mConfig, "localhost", 1883, "rsalm", "rsalm" );
	ASSERT_NE( mosquitto, nullptr);
}

TEST_F( ConstructFeature, Interface )
{
	IMosquitto* mosquitto = new Mosquitto( mConfig, "localhost", 1883, "rsalm", "rsalm" );
	ASSERT_NE( mosquitto, nullptr);
}

TEST_F( ConstructFeature, Builder )
{
	auto mosquitto = Mosquitto::builder.Build( "Mosquitto" );
	ASSERT_EQ( typeid( Generic ), typeid( mosquitto ) );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
