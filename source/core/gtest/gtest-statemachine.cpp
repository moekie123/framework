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

using gVisitor = NiceMock<MockMosquittoVisitor<0> >;
using gStateMachine = StateMachine<0>;

TEST( StateMachine, InitializeFailure )
{
        gVisitor visitor;
        gStateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( false ) );
        gStateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConfigureFailure )
{
        gVisitor visitor;
        gStateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitPreConfigure( testing::_ ) ).WillOnce( testing::Return( false ) );
        gStateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );
}

TEST( StateMachine, ConnectFailure )
{
        gVisitor visitor;
        gStateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitPreConfigure( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConnect( testing::_ ) ).WillOnce( testing::Return( false ) );
        gStateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );
}

TEST( StateMachine, LoopFailure )
{
        gVisitor visitor;
        gStateMachine::Accept( visitor );

        // UpStream
        EXPECT_CALL( visitor, visitInitialize( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitPreConfigure( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitConnect( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitPostConfigure( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitLoop( testing::_ ) ).WillOnce( testing::Return( false ) );
        gStateMachine::dispatch( eCycle() );

        // DownStream
        EXPECT_CALL( visitor, visitDisconnect( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitDestroy( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );

        EXPECT_CALL( visitor, visitCleanup( testing::_ ) ).WillOnce( testing::Return( true ) );
        gStateMachine::dispatch( eCycle() );
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
