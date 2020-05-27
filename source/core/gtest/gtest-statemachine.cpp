// Design Patterns
#include "Factory.h"
#include "Singleton.h"
#include "StateMachine.h"

// Testing
#include "mocks/MockConfigurator.h"
#include "mocks/MockMosquitto.h"
#include "mocks/MockParameter.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "tinyfsm.hpp"

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;
using ::testing::Return;

TEST( StateMachine, InitializeFailure )
{
        NiceMock<MockMosquittoVisitor> visitor;
        StateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( false ) );
        StateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConfigureFailure )
{
        NiceMock<MockMosquittoVisitor> visitor;
        StateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConfigure( testing::_ ) ).WillOnce( testing::Return( false ) );
        StateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConnectFailure )
{
        NiceMock<MockMosquittoVisitor> visitor;
        StateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConfigure( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConnect( testing::_ ) ).WillOnce( testing::Return( false ) );
        StateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );
}

TEST( StateMachine, LoopFailure )
{
        NiceMock<MockMosquittoVisitor> visitor;
        StateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConfigure( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConnect( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitLoop( testing::_ ) ).WillOnce( testing::Return( false ) );
        StateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDisconnect( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        StateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
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

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
