#include <gtest/gtest.h>
#include "../../ParameterRange.h"

TEST( Default, Construct)
{
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );
}

TEST( Default, GetDefaultMinimum )
{
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "minimum" ) , 0);
}

TEST( Default, GetDefaultMaximum )
{
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    ASSERT_EQ( p->getProperty( "maximum" ) , 0);
}

TEST( Default, SetValue )
{
    int min; 
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    p->setProperty( "minimum" , -42 );
    ASSERT_EQ( p->getProperty("minimum"), -42 );
    
    p->setProperty( "maximum" , 42 );
    ASSERT_EQ( p->getProperty("maximum"), 42 );
    
    p->setProperty( "value" , 21 );
    ASSERT_EQ( p->getProperty("value"), 21 );
}


TEST( Default, ExceedMinimum )
{
    int value, min; 
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    min = p->getProperty("minimum");
    value =  p->getProperty("value");
    p->setProperty( "value" , min-1 );
    ASSERT_EQ( p->getProperty("value"), value );

    p->setProperty( "minimum" , -42 );

    min = p->getProperty("minimum");
    value =  p->getProperty("value");
    p->setProperty( "value" , min-1 );
    ASSERT_EQ( p->getProperty("value"), value );
}

TEST( Default, ExceedMaximum )
{
    int value, max; 
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    max = p->getProperty("maximum");
    value =  p->getProperty("value");
    p->setProperty( "value" , max+1 );
    ASSERT_EQ( p->getProperty("value"), value );

    p->setProperty( "maximum" , 42 );

    max = p->getProperty("maximum");
    value =  p->getProperty("value");
    p->setProperty( "value" , max+1 );
    ASSERT_EQ( p->getProperty("value"), value );
}


TEST( Default, Reset )
{
    IParameter *p = new ParameterRange( "Parameter" );
    ASSERT_NE( p , nullptr );

    p->setProperty( "minimum" , -42 );
    p->setProperty( "maximum" , 42 );

    p->setProperty( "value" , 21 );
    ASSERT_NE( p->getProperty("value"), p->getProperty( "default" ));

    p->reset();
    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));

    p->setProperty( "default", 10 );
    p->setProperty( "value" , 21 );
    ASSERT_NE( p->getProperty("value"), p->getProperty( "default" ));
    
    p->reset();
    ASSERT_EQ( p->getProperty("value"), p->getProperty( "default" ));
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
