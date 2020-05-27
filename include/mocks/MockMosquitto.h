#pragma once

// Inheritance
#include "Generic.h"

// Design Patterns
#include "Visitor.h"

// Interfaces
#include "IMosquitto.h"

// Third-Party
#include <gmock/gmock.h>

class MockMosquittoVisitor : public Visitor
{
       public:
        MOCK_METHOD1( visitInitialize, bool( const StateMachine& ) );
        MOCK_METHOD1( visitConfigure, bool( const StateMachine& ) );
        MOCK_METHOD1( visitConnect, bool( const StateMachine& ) );
        MOCK_METHOD1( visitLoop, bool( const StateMachine& ) );
        MOCK_METHOD1( visitReconnect, bool( const StateMachine& ) );
        MOCK_METHOD1( visitDisconnect, bool( const StateMachine& ) );
        MOCK_METHOD1( visitDestroy, bool( const StateMachine& ) );
        MOCK_METHOD1( visitCleanup, bool( const StateMachine& ) );
};
