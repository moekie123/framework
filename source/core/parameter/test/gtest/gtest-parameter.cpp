#include "../../Parameter.h"
#include "IParameter.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Singleton.h"
#include "Factory.h"

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

class ConstructFeature: 
	public ::testing::Test 
{
	private:

	protected:
		NiceMock< MockConfigurator > mConfig;

    	virtual ~ConstructFeature() {}

    	virtual void SetUp() 
	{
		EXPECT_CALL( mConfig, GetInteger( "Parameter", "const"  , testing::_ )).WillRepeatedly( testing::Return( true ));
		EXPECT_CALL( mConfig, GetInteger( "Parameter", "default", testing::_ )).WillRepeatedly( testing::Return( true ));
		EXPECT_CALL( mConfig, GetInteger( "Parameter", "value"  , testing::_ )).WillRepeatedly( testing::Return( true));
	
		Singleton< MockConfigurator >::Register( mConfig );

		Factory& factory = Singleton< Factory >::Instance();
		factory.Register< MockConfigurator >( "Configurator" );
	}
};

// Other Test that we already trust a working Constructor
class ParameterFeature: 
	public ::testing::Test 
{
	private:
		int* mReturn;

	protected:
		MockConfigurator mConfig;
		IParameter* mParameter;

    	virtual ~ParameterFeature() {}

    	virtual void SetUp() 
	{
		mReturn = new int( 0 );

		EXPECT_CALL( mConfig, GetInteger( testing::_ , testing::_, testing::_ )).WillRepeatedly( testing::Return( false ));

		mParameter = new Parameter( mConfig, "Parameter" );
		ASSERT_NE( mParameter , nullptr );
	}

    	virtual void TearDown() 
	{
		delete mParameter;
		delete mReturn;
    	}
};


// Constructor Tests
TEST_F( ConstructFeature, Default)
{
	/* Configurator Mock is defined in the feature */	
	Parameter *p = new Parameter( mConfig, "Parameter" );
    	ASSERT_NE( p , nullptr );
}

TEST_F( ConstructFeature, Interface )
{
	/* Configurator Mock is defined in the feature */	
	IParameter *p = new Parameter( mConfig, "Parameter" );
    	ASSERT_NE( p , nullptr );
}

TEST_F( ConstructFeature, Builder )
{
	auto parameter = Parameter::builder.Build( "Parameter" );
	ASSERT_EQ( typeid( Generic ), typeid( parameter ) );
}


/**
 * GTest: get the name op the parameter 
 */
TEST_F( ParameterFeature, GetName )
{
    	ASSERT_EQ( mParameter->GetName(), "Parameter" );
}

/**
 * GTest: get default properties
 */
TEST_F( ParameterFeature, GetProperty )
{
	int _value;

	EXPECT_EQ( mParameter->GetProperty( "Parameter.const", _value ), true );
	EXPECT_EQ( _value, 0 );

    	EXPECT_EQ( mParameter->GetProperty( "Parameter.value", _value ), true );
	EXPECT_EQ( _value, 0 );

	EXPECT_EQ( mParameter->GetProperty( "Parameter.default" , _value ), true );
	EXPECT_EQ( _value, 0 );
}

/**
 * GTest: (Composite Pattern) Added nested parameter
 */
TEST_F( ParameterFeature, NestedGetPropertyParameters )
{
	int _value;

	Parameter *cParameter = new Parameter( mConfig, "Nested" );
	mParameter->Add( *cParameter );

	EXPECT_EQ( mParameter->GetProperty( "Parameter/Nested.const", _value ), true );
	EXPECT_EQ( _value, 0 );

    	EXPECT_EQ( mParameter->GetProperty( "Parameter/Nested.value", _value ), true );
	EXPECT_EQ( _value, 0 );

	EXPECT_EQ( mParameter->GetProperty( "Parameter/Nested.default" , _value ), true );
	EXPECT_EQ( _value, 0 );
}

/**
 * GTest: set default properties
 */
TEST_F( ParameterFeature, SetProperty )
{
	int _value;

	EXPECT_EQ( mParameter->SetProperty( "Parameter.value", 1 ), true );
	mParameter->GetProperty( "Parameter.value", _value );
	EXPECT_EQ( _value, 1 );

	EXPECT_EQ( mParameter->SetProperty( "Parameter.default", 1 ), true );
	mParameter->GetProperty( "Parameter.default", _value );
	EXPECT_EQ( _value, 1 );

	EXPECT_EQ( mParameter->SetProperty( "Parameter.const", 1 ), true );
	mParameter->GetProperty( "Parameter.const", _value );
	EXPECT_EQ( _value, 1 );
}

/**
 * GTest: (Composite Pattern) set default properties
 */
TEST_F( ParameterFeature, NestedSetPropertyParameters )
{
	int _value;

	Parameter *cParameter = new Parameter( mConfig, "Nested" );
	mParameter->Add( *cParameter );

	EXPECT_EQ( mParameter->SetProperty( "Parameter/Nested.value", 1 ), true );
	mParameter->GetProperty( "Parameter/Nested.value", _value );
	EXPECT_EQ( _value, 1 );

	EXPECT_EQ( mParameter->SetProperty( "Parameter/Nested.default", 1 ), true );
	mParameter->GetProperty( "Parameter/Nested.default", _value );
	EXPECT_EQ( _value, 1 );

	EXPECT_EQ( mParameter->SetProperty( "Parameter/Nested.const", 1 ), true );
	mParameter->GetProperty( "Parameter/Nested.const", _value );
	EXPECT_EQ( _value, 1 );
}

/**
 * GTest: Value is Default value at creation
 */
TEST_F( ParameterFeature, DefaultIsValue )
{
	int _value, _default;

    	ASSERT_EQ( mParameter->GetProperty( "Parameter.value", _value ), true );
	ASSERT_EQ( mParameter->GetProperty( "Parameter.default" , _default ), true );
	ASSERT_EQ( _value, _default );
}

/*
 * GTest: Verify behaviour of the const property
 */
TEST_F( ParameterFeature, SetConstValue )
{
	int _const, _value;

    	ASSERT_EQ( mParameter->GetProperty( "Parameter.const" , _const ), true );
	ASSERT_EQ( _const , 0 );

    	mParameter->SetProperty( "Parameter.value" , 42 );
    	ASSERT_EQ( mParameter->GetProperty("Parameter.value", _value ), true );
	ASSERT_EQ( _value, 42 );
    
	ASSERT_EQ( mParameter->SetProperty( "Parameter.const", 1 ) , true );
    	mParameter->GetProperty( "Parameter.const", _const );
	ASSERT_EQ( _const , 1 );

	ASSERT_EQ( mParameter->SetProperty( "Parameter.value" , 0 ), false );
    	mParameter->GetProperty("Parameter.value", _value );
	ASSERT_EQ( _value, 42 );

	ASSERT_EQ( mParameter->SetProperty( "Parameter.const" , 0 ), false ) ;
     	mParameter->GetProperty( "Parameter.const", _const );
	ASSERT_EQ( _const , 1 );
}

/*
 * GTest: (Composited Pattern) Verify behaviour of the const property
 */
TEST_F( ParameterFeature, NestedSetConstValue )
{
	int _const, _value;

	Parameter *cParameter = new Parameter( mConfig, "Nested" );
	mParameter->Add( *cParameter );

    	mParameter->GetProperty( "Parameter.const" , _const );

    	ASSERT_EQ( mParameter->GetProperty( "Parameter/Nested.const" , _const ), true );
	ASSERT_EQ( _const , 0 );

    	mParameter->SetProperty( "Parameter/Nested.value" , 42 );

    	ASSERT_EQ( mParameter->GetProperty("Parameter/Nested.value", _value ), true );
	ASSERT_EQ( _value, 42 );

	mParameter->SetProperty( "Parameter.const", 1 ) ;

	ASSERT_EQ( mParameter->SetProperty( "Parameter/Nested.value" , 0 ), false );
    	mParameter->GetProperty("Parameter/Nested.value", _value );
	ASSERT_EQ( _value, 42 );
}



/**
 * GTest: Verify the Reset functionallity
 */
TEST_F( ParameterFeature, Reset )
{
	int _value, _default;

	mParameter->SetProperty( "Parameter.value" , 42 );
	
	mParameter->GetProperty( "Parameter.value", _value );
	mParameter->GetProperty( "Parameter.default", _default );
    	ASSERT_NE( _value, _default );

    	mParameter->Reset();
 	mParameter->GetProperty( "Parameter.value", _value );
	mParameter->GetProperty( "Parameter.default", _default );
    	
	ASSERT_EQ( _value, _default );
}

/**
 * GTest: Verify the Reset functionallity
 */
TEST_F( ParameterFeature, NestedReset )
{
	int _value, _default;

	Parameter *cParameter = new Parameter( mConfig, "Nested" );
	mParameter->Add( *cParameter );

	mParameter->SetProperty( "Parameter/Nested.value" , 42 );

	mParameter->GetProperty( "Parameter/Nested.value", _value );
	mParameter->GetProperty( "Parameter/Nested.default", _default );
    	ASSERT_NE( _value, _default );

    	mParameter->Reset();

 	mParameter->GetProperty( "Parameter/Nested.value", _value );
	mParameter->GetProperty( "Parameter/Nested.default", _default );
	ASSERT_EQ( _value, _default );
}

/**
 * GTest: (Observer Pattern) Attach and Notify
 */
TEST_F( ParameterFeature, SingleAttachAndNotify )
{
	MockParameter mock;
 	
	mParameter->Attach( mock );
    	EXPECT_CALL( mock, Update( mParameter ));
    	
	mParameter->Notify();
}

/**
 * GTest: (Observer Pattern) Attach and Notify
 */
TEST_F( ParameterFeature, MultipleAttachAndNotify )
{
	MockParameter mock1;
 	MockParameter mock2;

	mParameter->Attach( mock1 );
 	mParameter->Attach( mock2 );
   
	EXPECT_CALL( mock1, Update( mParameter ));
    	EXPECT_CALL( mock2, Update( mParameter ));

	mParameter->Notify();
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
