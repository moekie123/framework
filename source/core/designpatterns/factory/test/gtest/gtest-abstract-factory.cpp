#include <gtest/gtest.h>

#include "designpatterns/AbstractFactory.h"
#include "designpatterns/Builder.h"

#include "Generic.h"
#include "Configurator.h"

#include <string>

class InterfaceBeta:
	public Generic
{
    public:
        virtual void execute() = 0;
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
		Generic* build( std::string _name ) override
		{
			return new ConcreteBeta();
		}
	};
	static ConcreteBetaBuilder builder;

    	void execute(){}
};
ConcreteBeta::ConcreteBetaBuilder ConcreteBeta::builder;

TEST( Construct, Default )
{
    Factory *f = new Factory;

    f->Register( "CB", &ConcreteBeta::builder );

    auto ab = f->Create< InterfaceBeta >( "CB", "Name" );

    ab->execute();

}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
