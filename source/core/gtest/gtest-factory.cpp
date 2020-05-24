#include <gtest/gtest.h>

#include "AbstractFactory.h"
#include "Factory.h"
#include "Builder.h"

#include "Generic.h"

#include <string>

class InterfaceBeta:
	public Generic
{
    public:
        virtual void execute(){ }
};

class ConcreteBeta:
    public InterfaceBeta
{
	public:
	/**
	 * Builder
	 */
	class ConcreteBetaBuilder:
		public Builder< InterfaceBeta >
	{
		public:
		static InterfaceBeta* Build( const std::string& _name ) 
		{
			InterfaceBeta* iBeta = new ConcreteBeta();
			return iBeta;
		}

		ConcreteBetaBuilder(): Builder( ConcreteBetaBuilder::Build )
		{

		}
	};
	static ConcreteBetaBuilder builder;

    	void execute()
	{
	
	}
};

ConcreteBeta::ConcreteBetaBuilder ConcreteBeta::builder;

TEST( Construct, Default )
{
	AbstractFactory< Factory< ConcreteBeta >> factory;
}

TEST( Register,  Default )
{
	AbstractFactory< Factory< InterfaceBeta >> factory;
	ASSERT_EQ( factory.Register< InterfaceBeta >( "CB", &ConcreteBeta::builder ), true );
}

TEST( Register,  AlreadyRegistered )
{
	AbstractFactory< Factory< InterfaceBeta >> factory;
	factory.Register< InterfaceBeta >( "CB", &ConcreteBeta::builder );

	ASSERT_ANY_THROW( factory.Register< InterfaceBeta >( "CB", &ConcreteBeta::builder ) );
}

TEST( Create, Default )
{
	AbstractFactory< Factory< InterfaceBeta >> factory;
	factory.Register< InterfaceBeta >( "CB", &ConcreteBeta::builder );

   	auto ab = factory.Construct< InterfaceBeta >( "CB" );
    	ab->execute();
}

TEST( Create, UnknownBuilder )
{
 	AbstractFactory< Factory< InterfaceBeta >> factory;
	factory.Register< InterfaceBeta >( "CB", &ConcreteBeta::builder );

	ASSERT_ANY_THROW( factory.Construct< InterfaceBeta >( "BC" ) );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
