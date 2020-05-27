// Inheritance
#include "Generic.h"

// Design Pattern
#include "Composite.h"

// Testing
#include "mocks/MockGeneric.h"

// Third Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Stl-Headers
#include <string>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

/* All classes that inherent the Composite Class should be included in these unit-tests */

template <typename T>
struct TypedTest : public testing::Test
{
        using ClassType = T;
};

/* Define here which classes in the framework are inheriting Composite */
using Types = testing::Types<Composite,
                             Generic
                             /* Navigating through the source three for the header files nasty */
                             // Parameter
                             // Actuator
                             // Mosquitto
                             >;

TYPED_TEST_CASE( TypedTest, Types );

TYPED_TEST( TypedTest, Default )
{
        using Class = typename TestFixture::ClassType;

        Composite *c = new Class();
        ASSERT_NE( c, nullptr );
}

TYPED_TEST( TypedTest, Add )
{
         MockGeneric mock;
        const std::string leafname = "Leaf";

        // The node is focus of this gtest
        using Class = typename TestFixture::ClassType;

        Composite *node = new Class();
        node->SetName( "Node" );

        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( leafname ) );
        EXPECT_CALL( mock, SetName( "Node/Leaf" ) ).WillOnce( testing::Return( true ) );
        node->Add( mock );
}

TYPED_TEST( TypedTest, GetAndSetProperty )
{
        MockGeneric mock;
        const std::string leafname = "Leaf";

        // The node is focus of this gtest
        using Class = typename TestFixture::ClassType;

        Composite *node = new Class();
        node->SetName( "Node" );

        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( leafname ) );
        EXPECT_CALL( mock, SetName( "Node/Leaf" ) ).WillOnce( testing::Return( true ) );
        node->Add( mock );

        int value = 42;
        node->SetProperty( "const", value );

        int result = 0;
        ASSERT_EQ( node->GetProperty( "const", result ), true );
        ASSERT_EQ( result, 42 );
}

TYPED_TEST( TypedTest, GetAndSetNamedProperty )
{
        MockGeneric mock;
        const std::string leafname = "Leaf";

        // The node is focus of this gtest
        using Class = typename TestFixture::ClassType;

        Composite *node = new Class();
        node->SetName( "Node" );

        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( leafname ) );
        EXPECT_CALL( mock, SetName( "Node/Leaf" ) ).WillOnce( testing::Return( true ) );
        node->Add( mock );

        int value = 42;
        node->SetProperty( "Node.const", value );

        int result = 0;
        ASSERT_EQ( node->GetProperty( "Node.const", result ), true );
        ASSERT_EQ( result, 42 );
}

TYPED_TEST( TypedTest, GetAndSetNestedProperty )
{
        MockGeneric mock;
        const std::string leafname = "Leaf";

        // The node is focus of this gtest
        using Class = typename TestFixture::ClassType;

        Composite *node = new Class();
        node->SetName( "Node" );

        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( leafname ) );
        EXPECT_CALL( mock, SetName( "Node/Leaf" ) ).WillOnce( testing::Return( true ) );
        node->Add( mock );

        int value = 42;
        EXPECT_CALL( mock, SetProperty( "Node/Leaf.const", testing::_ ) ).WillOnce( testing::Return( true ) );
        node->SetProperty( "Node/Leaf.const", value );

        int result = 0;
        EXPECT_CALL( mock, GetProperty( "Node/Leaf.const", testing::_ ) ).WillOnce( testing::Return( true ) );
        ASSERT_EQ( node->GetProperty( "Node/Leaf.const", result ), true );
}

TYPED_TEST( TypedTest, Reset )
{
        MockGeneric mock;
        const std::string leafname = "Leaf";

        // The node is focus of this gtest
        using Class = typename TestFixture::ClassType;

        Composite *node = new Class();
        node->SetName( "Node" );

        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( leafname ) );
        EXPECT_CALL( mock, SetName( "Node/Leaf" ) ).WillOnce( testing::Return( true ) );
        node->Add( mock );

        EXPECT_CALL( mock, Reset() ).WillOnce( testing::Return( true ) );
        node->Reset();
}

int main( int argc, char **argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
