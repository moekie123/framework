#include "../../Actuator.h"
#include "IActuator.h"

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
TEST_F( ConstructFeature, Default)
{
	/* Configurator Mock is defined in the feature */	
	Actuator *a = new Actuator( "Actuator" );
    	ASSERT_NE( a , nullptr );
}

TEST_F( ConstructFeature, Interface )
{
	/* Configurator Mock is defined in the feature */	
	IActuator *a = new Actuator( "Actuator" );
    	ASSERT_NE( a , nullptr );
}

TEST_F( ConstructFeature, Builder )
{
	auto actuator = Actuator::builder.Build( "Actuator" );
	ASSERT_EQ( typeid( Generic ), typeid( actuator ) );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
