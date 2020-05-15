#pragma once

#include "Generic.h"
#include "IMosquitto.h"
#include "../../Visitor.h"

#include <gmock/gmock.h>
#include <string>

class MockMosquittoVisitor: 
	public MosquittoVisitor
{
        public:
    		MOCK_METHOD1( visitInitialize, bool( const StateMachine& ));
    		MOCK_METHOD1( visitConfigure, bool( const StateMachine& ));
    		MOCK_METHOD1( visitConnect, bool( const StateMachine& ));
    		MOCK_METHOD1( visitLoop, bool( const StateMachine& ));
    		MOCK_METHOD1( visitReconnect, bool( const StateMachine& ));
    		MOCK_METHOD1( visitDisconnect, bool( const StateMachine& ));
    		MOCK_METHOD1( visitDestroy, bool( const StateMachine& ));
    		MOCK_METHOD1( visitCleanup, bool( const StateMachine& ));
};
