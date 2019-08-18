#include <gtest/gtest.h>
#include "../../ParameterRange.h"

#include "mocks/MockConfigurator.h"

TEST( Default, Construct)
{
	int value = 0;
	MockConfigurator config;
		
	EXPECT_CALL( config, getProperty( "Parameter.const" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.default" )).WillRepeatedly( testing::ReturnRef(value));
	EXPECT_CALL( config, getProperty( "Parameter.value" )).WillRepeatedly( testing::ReturnRef(value));

	IParameter *p = new ParameterRange( config, "Parameter" );
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

TEST_F( ParameterTest, GetDefaultMinimum )
{
	ASSERT_EQ( mParameter->getProperty( "minimum" ) , 0);
}

TEST_F( ParameterTest, GetDefaultMaximum )
{	
	ASSERT_EQ( mParameter->getProperty( "maximum" ) , 0);
}

TEST_F( ParameterTest, SetValue )
{	
	int min; 

	mParameter->setProperty( "minimum" , -42 );
	ASSERT_EQ( mParameter->getProperty("minimum"), -42 );
    
	mParameter->setProperty( "maximum" , 42 );
	ASSERT_EQ( mParameter->getProperty("maximum"), 42 );
    
	mParameter->setProperty( "value" , 21 );
	ASSERT_EQ( mParameter->getProperty("value"), 21 );
}


TEST_F( ParameterTest, ExceedMinimum )
{	
	int value, min; 
	mParameter->setProperty( "minimum" , -42 );
	min = mParameter->getProperty("minimum");
	
	mParameter->setProperty("value", 0 );
	value =  mParameter->getProperty("value");
	
	mParameter->setProperty( "value" , min-1 );
	ASSERT_EQ( mParameter->getProperty("value"), value );

	mParameter->setProperty( "minimum" , -42 );

	min = mParameter->getProperty("minimum");
	value =  mParameter->getProperty("value");
	mParameter->setProperty( "value" , min-1 );
	ASSERT_EQ( mParameter->getProperty("value"), value );
}

TEST_F( ParameterTest, ExceedMaximum )
{	
	int value, max; 
	max = mParameter->getProperty("maximum");

	mParameter->setProperty("value", 0 );
	value =  mParameter->getProperty("value");
	
	mParameter->setProperty( "value" , max+1 );
	ASSERT_EQ( mParameter->getProperty("value"), value );

	mParameter->setProperty( "maximum" , 42 );

	max = mParameter->getProperty("maximum");
	value =  mParameter->getProperty("value");
	mParameter->setProperty( "value" , max+1 );
	ASSERT_EQ( mParameter->getProperty("value"), value );
}


TEST_F( ParameterTest, Reset )
{
    	mParameter->setProperty( "minimum" , -42 );
    	mParameter->setProperty( "maximum" , 42 );

    	mParameter->setProperty( "value" , 21 );
    	ASSERT_NE( mParameter->getProperty("value"), mParameter->getProperty( "default" ));

    	mParameter->reset();
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));

    	mParameter->setProperty( "default", 10 );
    	mParameter->setProperty( "value" , 21 );
    	ASSERT_NE( mParameter->getProperty("value"), mParameter->getProperty( "default" ));
    
    	mParameter->reset();
    	ASSERT_EQ( mParameter->getProperty("value"), mParameter->getProperty( "default" ));
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
