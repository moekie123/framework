#pragma once

#include "StateMachine.h"

// Forward Declaration
class StateMachine;

class MosquittoVisitor
{
	public:
		virtual bool visitInitialize( const StateMachine& ) = 0;
		virtual bool visitConfigure( const StateMachine& ) = 0;
		virtual bool visitConnect( const StateMachine& ) = 0;

		virtual bool visitLoop( const StateMachine& ) = 0;

		virtual bool visitReconnect( const StateMachine& ) = 0;
		virtual bool visitDisconnect( const StateMachine& ) = 0;
		virtual bool visitDestroy( const StateMachine& ) = 0;
		virtual bool visitCleanup( const StateMachine& ) = 0;
};

