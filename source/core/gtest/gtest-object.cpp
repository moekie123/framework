// Inheritance
#include "Object.h"

// Third-Party
#include <gtest/gtest.h>

// Stl-Headers
#include <cstring>

TEST( Construct, Default )
{
        /* Builder is an interface class, not testing possible */
        Object* object = new Object();
}

TEST( Name, SetAndGetName )
{
        /* Builder is an interface class, not testing possible */
        Object* object = new Object();
        const std::string name = "object";

        ASSERT_EQ( object->GetName(), "" );

        ASSERT_EQ( object->SetName( name ), true );

        ASSERT_EQ( object->GetName(), name );
}

/**
 * GTest: get default properties
 */
TEST( ObjectFeature, GetProperty )
{
        int _value;
        Object* object = new Object();

        EXPECT_EQ( object->GetProperty( "const", _value ), true );
        EXPECT_EQ( _value, 0 );
}

/**
 * GTest: get default properties with name
 */
TEST( ObjectFeature, GetPropertyWithName )
{
        int _value;
        Object* object = new Object();

        object->SetName( "Object" );

        EXPECT_EQ( object->GetProperty( "const", _value ), true );
        EXPECT_EQ( _value, 0 );
}

/**
 * GTest: get unknown properties
 */
TEST( ObjectFeature, GetUnknownProperty )
{
        int _value = 123456789;
        Object* object = new Object();

        EXPECT_EQ( object->GetProperty( "unknown", _value ), false );
        EXPECT_EQ( _value, 123456789 );
}

/**
 * GTest: set default properties
 */
TEST( ObjectFeature, SetProperty )
{
        int _value = 0;
        Object* object = new Object();

        EXPECT_EQ( object->SetProperty( "const", 1 ), true );
        object->GetProperty( "const", _value );
        EXPECT_EQ( _value, 1 );
}

/**
 * GTest: set default properties
 */
TEST( ObjectFeature, SetPropertyWithName )
{
        int _value;

        Object* object = new Object();
        object->SetName( "Object" );

        EXPECT_EQ( object->SetProperty( "Object.const", 1 ), true );
        object->GetProperty( "Object.const", _value );
        EXPECT_EQ( _value, 1 );
}

/**
 * GTest: set unknown propertie
 */
TEST( ObjectFeature, SetUnknownProperty )
{
        Object* object = new Object();
        EXPECT_EQ( object->SetProperty( "unknown", 1 ), false );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
