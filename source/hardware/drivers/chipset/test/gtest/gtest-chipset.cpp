#include "../../Chipset.h"
#include "IChipset.h"

#include "mocks/MockConfigurator.h"
#include "mocks/MockSignal.h"
#include "mocks/MockParameter.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Singleton.h"
#include "Factory.h"

#include "IConfigurator.h"
#include "IParameter.h"

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
		Singleton< IConfigurator >::Register( mConfig );

		Factories *factory = new Factories();
		factory->Register< IConfigurator >( "Configurator", &MockConfigurator::builder );
		factory->Register< IParameter >( "Parameter", &MockParameter::builder );
	
		Singleton< Factories >::Register( *factory );
	}
};

// Constructor Tests
TEST_F( ConstructFeature, Default )
{
	IChipset* d = new Chipset( mConfig, "device" );
    	ASSERT_NE( d , nullptr );
}

TEST_F( ConstructFeature, Interface )
{
	IChipset* d = new Chipset( mConfig, "device" );
    	ASSERT_NE( d , nullptr );
}

TEST_F( ConstructFeature, Builder )
{
	auto chipset = Chipset::builder.Build( "Chipset" );
	ASSERT_EQ( typeid( IChipset* ), typeid( chipset ) );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
