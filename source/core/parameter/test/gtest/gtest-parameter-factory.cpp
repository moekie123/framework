#include <gtest/gtest.h>

#include "IParameter.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include "factory/ParameterFactory.h"

TEST( Construct, ParameterDefault )
{
    ParameterFactory pf;

    Factory& factory = Singleton< Factory >::Instance(); 
    auto ab = factory.create< IParameter >( "ParameterDefault", "<name>" );

    ASSERT_NE( ab, nullptr );
}

TEST( Construct, ParameterRange )
{
    ParameterFactory pf;

    Factory& factory = Singleton< Factory >::Instance(); 
    auto ab = factory.create< IParameter >( "ParameterRange", "<name>" );

    ASSERT_NE( ab, nullptr );

}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
