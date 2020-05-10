#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IConfigurator.h"
#include "../../Configurator.h"

#include <string>
#include <typeinfo>  

#include <unistd.h>
#include <iostream>

static std::string filename = "gtest-configurator.xml";

template<typename T>
struct TypedTest : public testing::Test
{
    using ParamType = T;
};

using Types = testing::Types<int, std::string>;
TYPED_TEST_CASE( TypedTest, Types);

TEST( Default, Construct )
{
	Configurator *cf1 = new Configurator( "gtest-configurator.xml" );

	Configurator *cf2 = new Configurator( "gtest-configurator.xml" );
}


TEST( Specalization, Integer )
{
	int value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	
	ASSERT_EQ( cf->GetProperty< int > ( "gtest-parameter" , "value", value ), true );
	ASSERT_EQ( value, 42 );
}

TEST( Specalization, String )
{
	std::string value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	
	ASSERT_EQ( cf->GetProperty< std::string > ( "gtest-parameter", "value", value ), true );
	ASSERT_EQ( value, "42" );
}

TEST( IntegerException, Unknown )
{
	int value;
	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< int > ( "unknown", "unknown", value ), false );
}

TYPED_TEST( TypedTest, UnknownNameAndAttribute )
{
	using ParamType  = typename TestFixture::ParamType;
	ParamType value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< ParamType > ( "unknown", "unknown", value ), false );
}

TYPED_TEST( TypedTest, UnknownName )
{
	using ParamType  = typename TestFixture::ParamType;
	ParamType value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< ParamType > ( "unknown", "value", value ), false );
}

TYPED_TEST( TypedTest, UnknownAttribute )
{
	using ParamType  = typename TestFixture::ParamType;
	ParamType value;

	IConfigurator *cf = new Configurator( "gtest-configurator.xml" );
	ASSERT_EQ( cf->GetProperty< ParamType > ( "gtest-parameter", "unknown", value ), false );
}



int main(int argc, char **argv) 
{

	if( access( filename.c_str(), F_OK ) != -1 )
	{
		Configurator::mConfigFileName = filename;
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}
	else
		std::cout << "Couldn't find [" << filename << "]\n";
	
	return 0;
}
