#include "../../Mosquitto.h"
#include "../../StateMachine.h"
#include "IMosquitto.h"

#include "MockMosquitto.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Singleton.h"
#include "Factory.h"

#include "tinyfsm.hpp"

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;
using ::testing::Return;

class MosquittoFeature: 
	public ::testing::Test 
{
	private:

	protected:
		NiceMock< MockConfigurator > mConfig;

    	virtual ~MosquittoFeature() {}

    	virtual void SetUp() 
	{
		mConfig.stringResults["hostname"] = "localhost";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "hostname", testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["port"]     = "1833";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "port", testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["username"] = "rsalm";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "username"  , testing::_ )).WillRepeatedly( testing::Return( true ));
	
		mConfig.stringResults["password"] = "rsalm";
		EXPECT_CALL( mConfig, GetString( "mosquitto", "password"  , testing::_ )).WillRepeatedly( testing::Return( true ));

		Singleton< MockConfigurator >::Register( mConfig );

		Factory& factory = Singleton< Factory >::Instance();

		factory.Register< MockConfigurator >( "Configurator" );
	}
};

/**
 * GTest: Construct the client
 */
TEST_F( MosquittoFeature, Default )
{
	Mosquitto* mosquitto = new Mosquitto( mConfig, "localhost", 1883, "rsalm", "rsalm" );
	ASSERT_NE( mosquitto, nullptr);
}

TEST_F( MosquittoFeature, Interface )
{
	IMosquitto* mosquitto = new Mosquitto( mConfig, "localhost", 1883, "rsalm", "rsalm" );
	ASSERT_NE( mosquitto, nullptr);
}

TEST_F( MosquittoFeature, Builder )
{
	auto mosquitto = Mosquitto::builder.Build( "Mosquitto" );
	ASSERT_EQ( typeid( Generic ), typeid( mosquitto ) );
}


bool terminate()
{
	std::cout << "TEST\n";	
	StateMachine::dispatch( eTerminate() );
	return false;
}

TEST( StateMachine, InitializeFailure )
{
	NiceMock< MockMosquittoVisitor > visitor;
	StateMachine::Accept( visitor );	

	// UpStream
	EXPECT_CALL( visitor, visitInitialize( testing::_ )).WillOnce( testing::Return( false ));
	StateMachine::dispatch( eCycle() );

	// DownStream
	EXPECT_CALL( visitor, visitCleanup( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConfigureFailure )
{
	NiceMock< MockMosquittoVisitor > visitor;
	StateMachine::Accept( visitor );	

	// UpStream
	EXPECT_CALL( visitor, visitInitialize( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitConfigure( testing::_ )).WillOnce( testing::Return( false ) );
	StateMachine::dispatch( eCycle() );

	// DownStream
	EXPECT_CALL( visitor, visitDestroy( testing::_ )).WillOnce( testing::Return( true ) );
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitCleanup( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConnectFailure )
{
	NiceMock< MockMosquittoVisitor > visitor;
	StateMachine::Accept( visitor );
	
	// UpStream
	EXPECT_CALL( visitor, visitInitialize( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitConfigure( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitConnect( testing::_ )).WillOnce( testing::Return( false ));
	StateMachine::dispatch( eCycle() );

	// DownStream
	EXPECT_CALL( visitor, visitDestroy( testing::_ )).WillOnce( testing::Return( true ) );
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitCleanup( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

}

TEST( StateMachine, LoopFailure )
{
	NiceMock< MockMosquittoVisitor > visitor;
	StateMachine::Accept( visitor );	

	// UpStream
	EXPECT_CALL( visitor, visitInitialize( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitConfigure( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitConnect( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitLoop( testing::_ )).WillOnce( testing::Return( false ) );
	StateMachine::dispatch( eCycle() );

	// DownStream
	EXPECT_CALL( visitor, visitDisconnect( testing::_ )).WillOnce( testing::Return( true ) );
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitDestroy( testing::_ )).WillOnce( testing::Return( true ) );
	StateMachine::dispatch( eCycle() );

	EXPECT_CALL( visitor, visitCleanup( testing::_ )).WillOnce( testing::Return( true ));
	StateMachine::dispatch( eCycle() );

}

/* DONT MODIFY, THIS IS A TEMPLATE 
TEST( StateMachine, InitializeFailure )
{
	NiceMock< MockMosquittoVisitor > visitor;

	EXPECT_CALL( visitor, visitInitialize( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitConfigure( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitConnect( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitLoop( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitReconnect( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitDisconnect( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitDestroy( testing::_ )).WillOnce( testing::Return( true ) );
	EXPECT_CALL( visitor, visitCleanup( testing::_ )).WillOnce( testing::Return( true ) )1;

	StateMachine::Accept( visitor );	
}
*/

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
