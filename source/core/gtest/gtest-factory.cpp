// Inheriance

// Interfaces
#include "IConfigurator.h"

// Testing
#include "mocks/MockConfigurator.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Stl-Header
#include <string>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

class InterfaceBeta : public Generic
{
       public:
        virtual void execute() {}
};

class ConcreteBeta : public InterfaceBeta
{
       public:
        /**
	 * Builder
	 */
        class ConcreteBetaBuilder : public Builder<InterfaceBeta>
        {
               public:
                static InterfaceBeta* Build( const IConfigurator*, const std::string& _name )
                {
                        InterfaceBeta* iBeta = new ConcreteBeta();
                        return iBeta;
                }

                ConcreteBetaBuilder() : Builder( ConcreteBetaBuilder::Build )
                {
                }
        };
        static ConcreteBetaBuilder builder;

        void execute()
        {
        }
};

ConcreteBeta::ConcreteBetaBuilder ConcreteBeta::builder;
using TestFactories = AbstractFactory<Factory<InterfaceBeta>,
                                      Factory<IConfigurator>>;

TEST( Construct, Default )
{
        TestFactories factory;
}

TEST( Register, Default )
{
        TestFactories factory;
        ASSERT_EQ( factory.Register<InterfaceBeta>( "CB", &ConcreteBeta::builder ), true );
}

TEST( Register, AlreadyRegistered )
{
        TestFactories factory;
        factory.Register<InterfaceBeta>( "CB", &ConcreteBeta::builder );

        ASSERT_ANY_THROW( factory.Register<InterfaceBeta>( "CB", &ConcreteBeta::builder ) );
}

TEST( Create, Default )
{
        // Construct Factory
        TestFactories factory;

        // Construct and register configurator
        NiceMock<MockConfigurator> mConfig;
        Singleton<IConfigurator>::Register( mConfig );
        factory.Register<IConfigurator>( "Configurator", &MockConfigurator::builder );

        // Register builder
        factory.Register<InterfaceBeta>( "CB", &ConcreteBeta::builder );

        auto ab = factory.Construct<InterfaceBeta>( "CB" );
        ab->execute();
}

TEST( Create, UnknownBuilder )
{
        TestFactories factory;

        factory.Register<InterfaceBeta>( "CB", &ConcreteBeta::builder );

        ASSERT_ANY_THROW( factory.Construct<InterfaceBeta>( "BC" ) );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
