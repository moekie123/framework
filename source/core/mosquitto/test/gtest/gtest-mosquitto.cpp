//#include "../../Mosquitto.h"
#include "IMosquitto.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

/**
 * GTest: Construct the client
 */
TEST( Default, Construct)
{
	int value = 0;
	NiceMock< MockConfigurator > config;
		
	/* See MockConfigurator fot GetInteger
	 * This is a workaround for the ambgious Get 
	 **/
	EXPECT_CALL( config, GetString( "Mosquitto", "hostname"  , testing::_ )).WillRepeatedly( testing::Return( true ));
	EXPECT_CALL( config, GetString( "Mosquitto", "port", testing::_ )).WillRepeatedly( testing::Return( true ));
	EXPECT_CALL( config, GetString( "Mosquitto", "username"  , testing::_ )).WillRepeatedly( testing::Return( true));
	EXPECT_CALL( config, GetString( "Mosquitto", "password"  , testing::_ )).WillRepeatedly( testing::Return( true));

//	Mosquitto* mosquitto = new Mosquitto( &config );
//	ASSERT_NE( mosquitto, nullptr);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
