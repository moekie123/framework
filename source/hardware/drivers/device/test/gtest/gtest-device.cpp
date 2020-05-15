#include "../../Device.h"
#include "IDevice.h"

#include "mocks/MockConfigurator.h"
#include "mocks/MockSignal.h"
#include "mocks/MockParameter.h"

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
		NiceMock< MockParameter > mParameter;

    	virtual ~ConstructFeature() {}

    	virtual void SetUp() 
	{
		Factory& factory = Singleton< Factory >::Instance();

//		EXPECT_CALL( mConfig, GetInteger( "Parameter", "value"  , testing::_ )).WillRepeatedly( testing::Return( true));
		Singleton< MockConfigurator >::Register( mConfig );
		factory.Register< MockConfigurator >( "Configurator" );

//		EXPECT_CALL( mConfig, GetInteger( "Parameter", "value"  , testing::_ )).WillRepeatedly( testing::Return( true));
		Singleton< MockParameter >::Register( mParameter );
		factory.Register< MockParameter >( "Parameter" );
	}
};

// Constructor Tests
TEST_F( ConstructFeature, Default )
{
	MockSignal period;
	MockSignal dutycycle;

	IDevice* d = new Device( mConfig, "device" , period, dutycycle );
    	ASSERT_NE( d , nullptr );
}

TEST_F( ConstructFeature, Interface )
{
	MockSignal period;
	MockSignal dutycycle;

	IDevice* d = new Device( mConfig, "device" , period, dutycycle );
    	ASSERT_NE( d , nullptr );
}

TEST_F( ConstructFeature, Builder )
{
	auto device = Device::builder.Build( "device" );
	ASSERT_EQ( typeid( Generic ), typeid( device ) );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
