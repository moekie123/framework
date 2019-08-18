#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include "IParameter.h"
#include "../../Parameter.h"

#include <iostream>

// Constructor Tests
TEST( Default, Construct)
{
	int value = 0;
	MockConfigurator config;
		
	EXPECT_CALL( config, getProperty( "Parameter.const" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.default" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.value" )).WillRepeatedly( testing::ReturnRef(value));

	IParameter *p = new Parameter( config, "Parameter" );
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
	
		mParameter = new Parameter( mConfig, "Parameter" );
		ASSERT_NE( mParameter , nullptr );
	}

    	virtual void TearDown() 
	{
		delete mParameter;
		delete mReturn;
    	}

};

TEST_F( ParameterTest, GetName )
{
    	ASSERT_EQ( mParameter->getName(), "Parameter" );
}

TEST_F( ParameterTest, GetValue )
{
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));
}

TEST_F( ParameterTest, SetValue )
{
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));

    	mParameter->setProperty( "value" , 42 );
    	ASSERT_EQ( mParameter->getProperty("value"), 42 );
}

TEST_F( ParameterTest, SetConstValue )
{
    	ASSERT_EQ( mParameter->getProperty( "const" ), 0 );

    	mParameter->setProperty( "value" , 42 );
    	ASSERT_EQ( mParameter->getProperty("value"), 42 );
    
    	mParameter->setProperty( "const" , 1 );
    	ASSERT_EQ( mParameter->getProperty( "const" ), 1 );

    	mParameter->setProperty( "value" , 0 );
    	ASSERT_EQ( mParameter->getProperty("value"), 42 );

    	mParameter->setProperty( "const" , 0 );
    	ASSERT_EQ( mParameter->getProperty( "const" ), 1 );
}

TEST_F( ParameterTest, GetPropertyDefault)
{
    	ASSERT_EQ( mParameter->getProperty( "default" ), 0 );
}

TEST_F( ParameterTest, SetPropertyDefault)
{
    	ASSERT_EQ( mParameter->getProperty( "default" ), 0 );

    	mParameter->setProperty( "default" , 42 );
    	ASSERT_EQ( mParameter->getProperty( "default" ), 42 );
}

TEST_F( ParameterTest, GetPropertyConst)
{
    	ASSERT_EQ( mParameter->getProperty( "const" ), 0 );
}

TEST_F( ParameterTest, SetPropertyConst)
{
    	ASSERT_EQ( mParameter->getProperty( "const" ), 0 );
    	mParameter->setProperty( "const" , 1 );

    	ASSERT_EQ( mParameter->getProperty( "const" ), 1 );
}

TEST_F( ParameterTest, Reset )
{
    	mParameter->setProperty( "value" , 42 );
    	ASSERT_NE( mParameter->getProperty("value"), mParameter->getProperty( "default" ));

    	mParameter->reset();
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));

    	mParameter->setProperty( "default", 21 );
    	mParameter->setProperty( "value" , 42 );
    	ASSERT_NE( mParameter->getProperty("value"), mParameter->getProperty( "default" ));
    
    	mParameter->reset();
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));
}

TEST_F( ParameterTest, AttachAndNotify)
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
