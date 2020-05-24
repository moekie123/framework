// Inheritance
#include "Generic.h"

// Third-Party
#include <gtest/gtest.h>

// Stl-Headers
#include <cstring>

TEST( Construct, Default )
{
	/* Builder is an interface class, not testing possible */
	Generic* generic = new Generic();	
}

TEST( Name, SetAndGetName )
{
	/* Builder is an interface class, not testing possible */
	Generic* generic = new Generic();
	const std::string name = "generic";

	ASSERT_EQ( generic->GetName(), "" );

	ASSERT_EQ( generic->SetName( name ), true );

	ASSERT_EQ( generic->GetName(), name );
}

/**
 * GTest: get default properties
 */
TEST( GenericFeature, GetProperty )
{
	int _value;
	Generic* generic = new Generic();

	EXPECT_EQ( generic->GetProperty( "const", _value ), true );
	EXPECT_EQ( _value, 0 );
}

/**
 * GTest: get default properties with name
 */
TEST( GenericFeature, GetPropertyWithName )
{
	int _value;
	Generic* generic = new Generic();
	
	generic->SetName( "Generic" );

	EXPECT_EQ( generic->GetProperty( "const", _value ), true );
	EXPECT_EQ( _value, 0 );
}

/**
 * GTest: get unknown properties
 */
TEST( GenericFeature, GetUnknownProperty )
{
	int _value = 123456789;
	Generic* generic = new Generic();

	EXPECT_EQ( generic->GetProperty( "unknown", _value ), false );
	EXPECT_EQ( _value, 123456789 );
}


/**
 * GTest: set default properties
 */
TEST( GenericFeature, SetProperty )
{
	int _value = 0;
	Generic* generic = new Generic();

	EXPECT_EQ( generic->SetProperty( "const", 1 ), true );
	generic->GetProperty( "const", _value );
	EXPECT_EQ( _value, 1 );
}

/**
 * GTest: set default properties
 */
TEST( GenericFeature, SetPropertyWithName )
{
	int _value;

	Generic* generic = new Generic();
	generic->SetName( "Generic" );

	EXPECT_EQ( generic->SetProperty( "Generic.const", 1 ), true );
	generic->GetProperty( "Generic.const", _value );
	EXPECT_EQ( _value, 1 );
}

/**
 * GTest: set unknown propertie
 */
TEST( GenericFeature, SetUnknownProperty )
{
	Generic* generic = new Generic();
	EXPECT_EQ( generic->SetProperty( "unknown", 1 ), false );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
