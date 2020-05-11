#include <gtest/gtest.h>

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
		public Builder
	{
		public:
		Generic& Build( const std::string& _name ) override
		{
			InterfaceBeta* iBeta = new ConcreteBeta();
			return *iBeta;
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
    Factory *f = new Factory;
}

TEST( Register,  Default )
{
    Factory *f = new Factory;
    ASSERT_EQ( f->Register< ConcreteBeta >( "CB" ), true );
}

TEST( Register,  AlreadyRegistered )
{
    Factory *f = new Factory;
    f->Register< ConcreteBeta >( "CB" );

    ASSERT_EQ( f->Register< ConcreteBeta >( "CB" ), false );
}

TEST( Create, Default )
{
    Factory *f = new Factory;
    ASSERT_EQ( f->Register< ConcreteBeta >( "CB" ), true );
    
    auto ab = f->Create< InterfaceBeta >( "CB", "Name" );
    ab.execute();
}

TEST( Create, UnknownBuilder )
{
    	Factory *f = new Factory;
	ASSERT_ANY_THROW( f->Create< InterfaceBeta >( "BC", "Name" ) );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
