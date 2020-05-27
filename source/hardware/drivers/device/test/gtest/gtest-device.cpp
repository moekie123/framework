// Inheritance
#include "../../Device.h"

// Interface
#include "IDevice.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"

// Testing
#include "mocks/MockConfigurator.h"
#include "mocks/MockParameter.h"
#include "mocks/MockSignal.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

class ConstructFeature : public ::testing::Test
{
       private:
       protected:
        NiceMock<MockConfigurator> mConfig;
        NiceMock<MockParameter> mParameter;

        virtual ~ConstructFeature() {}

        virtual void SetUp()
        {
                if ( !Singleton<IConfigurator>::IsConstructed() )
                {
                	Singleton<IConfigurator>::Register( mConfig );
		}

                if ( !Singleton<Factories>::IsConstructed() )
                {
			Factories* factory = new Factories();
			factory->Register<IConfigurator>( "Configurator", &MockConfigurator::builder );
			factory->Register<IParameter>( "Parameter", &MockParameter::builder );

			Singleton<Factories>::Register( *factory );
                }
        }
};

// Constructor Tests
TEST_F( ConstructFeature, Default )
{
        MockSignal period;
        MockSignal dutycycle;

        IDevice* d = new Device( mConfig, "device", period, dutycycle );
        ASSERT_NE( d, nullptr );
}

TEST_F( ConstructFeature, Interface )
{
        MockSignal period;
        MockSignal dutycycle;

        IDevice* d = new Device( mConfig, "device", period, dutycycle );
        ASSERT_NE( d, nullptr );
}

TEST_F( ConstructFeature, Builder )
{
        auto device = Device::builder.Build( &mConfig, "Device" );
        ASSERT_EQ( typeid( IDevice* ), typeid( device ) );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
