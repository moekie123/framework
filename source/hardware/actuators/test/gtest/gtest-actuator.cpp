// Inheritance
#include "../../Actuator.h"

// Interfaces
#include "IActuator.h"

// Design Pattern
#include "Factory.h"
#include "Singleton.h"

// Testing
#include "mocks/MockConfigurator.h"
#include "mocks/MockParameter.h"

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
                        Factories *factory = new Factories();
                        factory->Register<IConfigurator>( "Configurator", &MockConfigurator::builder );
                        factory->Register<IParameter>( "Parameter", &MockParameter::builder );

                        Singleton<Factories>::Register( *factory );
                }
        }
};

// Constructor Tests
TEST_F( ConstructFeature, Default )
{
        /* Configurator Mock is defined in the feature */
        Actuator *a = new Actuator( "Actuator" );
        ASSERT_NE( a, nullptr );
}

TEST_F( ConstructFeature, Interface )
{
        /* Configurator Mock is defined in the feature */
        IActuator *a = new Actuator( "Actuator" );
        ASSERT_NE( a, nullptr );
}

TEST_F( ConstructFeature, Builder )
{
        auto actuator = Actuator::builder.Build( &mConfig, "Actuator" );
        ASSERT_EQ( typeid( IActuator * ), typeid( actuator ) );
}

int main( int argc, char **argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
