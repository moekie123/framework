#pragma once

// Inheritance
#include "Generic.h"

// Design Patterns
#include "Visitor.h"
//#include "StateMachine.h"

// Interfaces
#include "IMosquitto.h"

// Third-Party
#include <gmock/gmock.h>

template <int inum>
class MockMosquittoVisitor : public Visitor<inum>
{
          using base = StateMachine<inum>;
 
     public:
        MOCK_METHOD1( visitInitialize, bool( const base& ) );
        MOCK_METHOD1( visitPreConfigure, bool( const base& ) );
        MOCK_METHOD1( visitConnect, bool( const base& ) );
        MOCK_METHOD1( visitPostConfigure, bool( const base& ) );
        MOCK_METHOD1( visitLoop, bool( const base& ) );
        MOCK_METHOD1( visitReconnect, bool( const base& ) );
        MOCK_METHOD1( visitDisconnect, bool( const base& ) );
        MOCK_METHOD1( visitDestroy, bool( const base& ) );
        MOCK_METHOD1( visitCleanup, bool( const base& ) );
};
