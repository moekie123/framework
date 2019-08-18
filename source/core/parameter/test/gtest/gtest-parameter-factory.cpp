#include <gtest/gtest.h>

#include "IParameter.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include "../../Parameter.h"

TEST( Construct, ParameterDefault )
{
	Factory& factory = Singleton< Factory >::Instance();
	factory.Register( "Parameter",  &Parameter::builder );
	
    	auto ab = factory.Create< IParameter >( "Parameter", "<name>" );

    	ASSERT_NE( ab, nullptr );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
