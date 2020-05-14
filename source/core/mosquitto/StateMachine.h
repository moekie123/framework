#pragma once 

#include "Visitor.h"

#include "tinyfsm.hpp"
#include <iostream>
#include <string>

#include <unistd.h>

// StateMachine Events
struct eCycle : tinyfsm::Event { };

struct eSucces : tinyfsm::Event { };
struct eFailed : tinyfsm::Event { };

struct eTerminate : tinyfsm::Event { };

// Forward Declaration
class MosquittoVisitor;

// Base StateMachine
class StateMachine
	:public tinyfsm::Fsm< StateMachine >
{
public:

	StateMachine()
	{

	}

	StateMachine( std::string _name ):mName( _name )
	{

	}
	
	StateMachine& operator=( const StateMachine & other ) 
	{
		return *this;
	}

	virtual void entry( void )
	{
		std::cout << "StateMachine: S[" << mName << "] E[OnEntry]\n";
	}

	virtual void exit( void )
	{
		std::cout << "StateMachine: S[" << mName << "] E[OnExit]\n";
	}

	static void reset( void );

	/* Events */
	virtual void react( eCycle const & ){};

	virtual void react( eSucces const & ){};
	virtual void react( eFailed const & ){};

	virtual void react( eTerminate const & ){};

	const std::string& GetStateName()
	{
		return mName;
	}

	static void Accept( MosquittoVisitor& _visitor )
	{
		std::cout << "Visitor Accepted\n";
		
		mClient	= &_visitor;
		
		StateMachine::start();

		mRunning = true;
		while( mRunning )
		{
			auto current_state = StateMachine::current_state_ptr;
			//std::cout << "Current State:" << current_state->GetStateName() << "\n";

			StateMachine::dispatch( eCycle() );

			usleep( 50000 );
		}
	}

protected:
	std::string mName;

	static MosquittoVisitor* mClient;
	static bool mRunning;
	static bool mShutdown;
};
