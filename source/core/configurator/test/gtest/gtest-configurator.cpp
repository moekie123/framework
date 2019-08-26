#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IConfigurator.h"
#include "../../Configurator.h"

#include <string>

TEST( Default, Construct )
{
	Configurator *cf = new Configurator( "gtest-configurator.xml" );
}

TEST( Specalization, Integer )
{
	int value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	
	ASSERT_EQ( cf->GetProperty< int > ( "gtest-parameter.value", value ), true );
	ASSERT_EQ( value, 42 );
}

TEST( Specalization, String )
{
	std::string value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	
	ASSERT_EQ( cf->GetProperty< std::string > ( "gtest-parameter.value", value ), true );
	ASSERT_EQ( value, "42" );
}

TEST( Exception, UnknownInteger )
{
	int value;
	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< int > ( "gtest-parameter.unknown", value ), false );
}

TEST( Exception, UnknownString )
{
	std::string value;
	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< std::string > ( "gtest-parameter.unknown", value ), false );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
