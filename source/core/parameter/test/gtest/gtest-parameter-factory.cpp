#include "../../Parameter.h"
#include "IParameter.h"

#include "Singleton.h"
#include "Factory.h"

#include <gtest/gtest.h>

TEST( Construct, ParameterDefault )
{
	Factory& factory = Singleton< Factory >::Instance();
	factory.Register< Parameter >( "Parameter" );

	
	auto param = factory.Create< IParameter >( "Parameter", "<name>" );

    	ASSERT_NE( param, nullptr );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
