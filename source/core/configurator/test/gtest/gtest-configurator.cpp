#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../Configurator.h"

#include <string>

TEST( Default, Construct )
{
	Configurator *cf = new Configurator( "gtest-configurator.xml" );
}

TEST( Default, GetValue )
{	
	Configurator *cf = new Configurator( "gtest-configurator.xml" );
	
	int value;
	ASSERT_EQ( cf->getProperty( "gtest-parameter.value", value ), true );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
