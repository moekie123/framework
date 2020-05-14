#include "../../Mosquitto.h"

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
	NiceMock< MockConfigurator > config;
	
	config.stringResults["hostname"] = "localhost";
	config.stringResults["port"]     = "1833";
	config.stringResults["username"] = "rsalm";
	config.stringResults["password"] = "rsalm";

	EXPECT_CALL( config, GetString( "mosquitto", "hostname", testing::_ )).WillRepeatedly( testing::Return( true ));
	EXPECT_CALL( config, GetString( "mosquitto", "port", testing::_ )).WillRepeatedly( testing::Return( true ));
	EXPECT_CALL( config, GetString( "mosquitto", "username"  , testing::_ )).WillRepeatedly( testing::Return( true ));
	EXPECT_CALL( config, GetString( "mosquitto", "password"  , testing::_ )).WillRepeatedly( testing::Return( true ));

	Mosquitto* mosquitto = new Mosquitto( config );
	ASSERT_NE( mosquitto, nullptr);
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
