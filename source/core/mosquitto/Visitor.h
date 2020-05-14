#pragma once

#include "StateMachine.h"

// Forward Declaration
class MqttStateMachine;

class MosquittoVisitor
{
	public:
		virtual bool visitInitialize( const MqttStateMachine& ) = 0;
		virtual bool visitConfigure( const MqttStateMachine& ) = 0;
		virtual bool visitConnect( const MqttStateMachine& ) = 0;

		virtual bool visitLoop( const MqttStateMachine& ) = 0;

		virtual bool visitReconnect( const MqttStateMachine& ) = 0;
		virtual bool visitDisconnect( const MqttStateMachine& ) = 0;
		virtual bool visitDestroy( const MqttStateMachine& ) = 0;
		virtual bool visitCleanup( const MqttStateMachine& ) = 0;
};

