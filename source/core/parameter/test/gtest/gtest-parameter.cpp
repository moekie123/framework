#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mocks/MockParameter.h"

#include "IParameter.h"
#include "../../Parameter.h"

TEST( Default, Construct)
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );
}

TEST( Default, GetName )
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getName(), "Parameter" );
}

TEST( Default, GetValue )
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));
}

TEST( Default, SetValue )
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));

    p->setProperty( "value" , 42 );
    ASSERT_EQ( p->getProperty("value"), 42 );
}

TEST( Default, SetConstValue )
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "const" ), 0 );

    p->setProperty( "value" , 42 );
    ASSERT_EQ( p->getProperty("value"), 42 );
    
    p->setProperty( "const" , 1 );
    ASSERT_EQ( p->getProperty( "const" ), 1 );

    p->setProperty( "value" , 0 );
    ASSERT_EQ( p->getProperty("value"), 42 );

    p->setProperty( "const" , 0 );
    ASSERT_EQ( p->getProperty( "const" ), 1 );
}

TEST( Default, GetPropertyDefault)
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "default" ), 0 );
}

TEST( Default, SetPropertyDefault)
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "default" ), 0 );

    p->setProperty( "default" , 42 );
    ASSERT_EQ( p->getProperty( "default" ), 42 );
}

TEST( Default, GetPropertyConst)
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "const" ), 0 );
}

TEST( Default, SetPropertyConst)
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "const" ), 0 );
    p->setProperty( "const" , 1 );

    ASSERT_EQ( p->getProperty( "const" ), 1 );
}

TEST( Default, Reset )
{
    IParameter *p = new Parameter( "Parameter" );
    ASSERT_NE( p , nullptr );

    p->setProperty( "value" , 42 );
    ASSERT_NE( p->getProperty("value"), p->getProperty( "default" ));

    p->reset();
    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));

    p->setProperty( "default", 21 );
    p->setProperty( "value" , 42 );
    ASSERT_NE( p->getProperty("value"), p->getProperty( "default" ));
    
    p->reset();
    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));
}

TEST( Observer, AttachAndNotify)
{
    MockParameter mock;
    IParameter *p = new Parameter( "Parameter" );

    p->attach( mock );

    EXPECT_CALL( mock, update( p ));
    p->notify();
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
