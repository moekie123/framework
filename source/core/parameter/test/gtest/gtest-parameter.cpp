#include "../../Parameter.h"
#include "IParameter.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Constructor Tests
TEST( Default, Construct)
{
	int value = 0;
	MockConfigurator config;
		
	EXPECT_CALL( config, getProperty( "Parameter.const" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.default" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.value" )).WillRepeatedly( testing::ReturnRef(value));

	IParameter *p = new Parameter( &config, "Parameter" );
    	ASSERT_NE( p , nullptr );
}


// Other Test that we already trust a working Constructor
class ParameterTest: 
	public ::testing::Test 
{
	private:
		int * mReturn;

	protected:
		MockConfigurator mConfig;
		IParameter* mParameter;

    	ParameterTest() 
	{
    	
	}

    	virtual ~ParameterTest() {}

    	virtual void SetUp() 
	{
		mReturn = new int( 0 );

		EXPECT_CALL( mConfig, getProperty( "Parameter.const" )).WillRepeatedly( testing::ReturnRef( *mReturn ));
		EXPECT_CALL( mConfig, getProperty( "Parameter.default" )).WillRepeatedly( testing::ReturnRef( *mReturn ));
		EXPECT_CALL( mConfig, getProperty( "Parameter.value" )).WillRepeatedly( testing::ReturnRef( *mReturn ));
	
		mParameter = new Parameter( &mConfig, "Parameter" );
		ASSERT_NE( mParameter , nullptr );
	}

    	virtual void TearDown() 
	{
		delete mParameter;
		delete mReturn;
    	}

};

/**
 * GTest: get the name op the parameter 
 */
TEST_F( ParameterTest, GetName )
{
    	ASSERT_EQ( mParameter->getName(), "Parameter" );
}

/**
 * GTest: get default properties
 */
TEST_F( ParameterTest, GetProperty )
{
	int _value;

	EXPECT_EQ( mParameter->getProperty( "const", _value ), true );
	EXPECT_EQ( _value, 0 );

    	EXPECT_EQ( mParameter->getProperty( "value", _value ), true );
	EXPECT_EQ( _value, 0 );

	EXPECT_EQ( mParameter->getProperty( "default" , _value ), true );
	EXPECT_EQ( _value, 0 );
}

/**
 * GTest: set default properties
 */
TEST_F( ParameterTest, SetProperty )
{
	int _value;

	EXPECT_EQ( mParameter->setProperty( "value", 1 ), true );
	mParameter->getProperty( "value", _value );
	EXPECT_EQ( _value, 0 );

	EXPECT_EQ( mParameter->setProperty( "default", 1 ), true );
	mParameter->getProperty( "default", _value );
	EXPECT_EQ( _value, 1 );

	EXPECT_EQ( mParameter->setProperty( "const", 1 ), true );
	mParameter->getProperty( "const", _value );
	EXPECT_EQ( _value, 1 );
}


/**
 * GTest: Value is Default value at creation
 */
TEST_F( ParameterTest, DefaultIsValue )
{
	int _value, _default;

    	ASSERT_EQ( mParameter->getProperty( "value", _value ), true );
	ASSERT_EQ( mParameter->getProperty( "default" , _default ), true );
	ASSERT_EQ( _value, _default );
}

/*
 * GTest: Verify behaviour of the const property
 */
TEST_F( ParameterTest, SetConstValue )
{
	int _const, _value;

    	ASSERT_EQ( mParameter->getProperty( "const" , _const ), true );
	ASSERT_EQ( _const , 0 );

    	mParameter->setProperty( "value" , 42 );
    	ASSERT_EQ( mParameter->getProperty("value", _value ), true );
	ASSERT_EQ( _value, 42 );
    
	ASSERT_EQ( mParameter->setProperty( "const", 1 ) , true );
    	mParameter->getProperty( "const", _const );
	ASSERT_EQ( _const , 1 );

	ASSERT_EQ( mParameter->setProperty( "value" , 0 ), false );
    	mParameter->getProperty("value", _value );
	ASSERT_EQ( _value, 42 );

	ASSERT_EQ( mParameter->setProperty( "const" , 0 ), false ) ;
     	mParameter->getProperty( "const", _const );
	ASSERT_EQ( _const , 1 );
}

/**
 * GTest: Verify the reset functionallity
 */
TEST_F( ParameterTest, Reset )
{
	int _value, _default;

	mParameter->setProperty( "value" , 42 );
	
	mParameter->getProperty( "value", _value );
	mParameter->getProperty( "default", _default );
    	ASSERT_NE( _value, _default );

    	mParameter->reset();
 	mParameter->getProperty( "value", _value );
	mParameter->getProperty( "default", _default );
    	ASSERT_EQ( _value, _default );
}

/**
 * GTest: (Observer Pattern) Attach and Notify
 */
TEST_F( ParameterTest, AttachAndNotify )
{
	MockParameter mock;
    	mParameter->attach( mock );

    	EXPECT_CALL( mock, update( mParameter ));
    	mParameter->notify();
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
