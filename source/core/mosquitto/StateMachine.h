#pragma once 

#include "Visitor.h"

#include "tinyfsm.hpp"
#include <iostream>
#include <string>

#include <unistd.h>

// StateMachine Events
struct MqttEventCycle : tinyfsm::Event { };

struct MqttEventSucces : tinyfsm::Event { };
struct MqttEventFailed : tinyfsm::Event { };

struct MqttEventTerminate : tinyfsm::Event { };

// Forward Declaration
class MosquittoVisitor;

// Base StateMachine
class MqttStateMachine
	:public tinyfsm::Fsm< MqttStateMachine >
{
public:

	MqttStateMachine()
	{

	}

	MqttStateMachine( std::string _name ):mName( _name )
	{

	}
	
	MqttStateMachine& operator=( const MqttStateMachine & other ) 
	{
		return *this;
	}

	virtual void entry( void )
	{
		std::cout << "MqttStateMachine: S[" << mName << "] E[OnEntry]\n";
	}

	virtual void exit( void )
	{
		std::cout << "MqttStateMachine: S[" << mName << "] E[OnExit]\n";
	}

	static void reset( void );

	/* Events */
	virtual void react( MqttEventCycle const & ){};

	virtual void react( MqttEventSucces const & ){};
	virtual void react( MqttEventFailed const & ){};

	virtual void react( MqttEventTerminate const & ){};

	const std::string& GetStateName()
	{
		return mName;
	}

	static void Accept( MosquittoVisitor& _visitor )
	{
		std::cout << "Visitor Accepted\n";
		
		mClient	= &_visitor;
		
		MqttStateMachine::start();

		mRunning = true;
		while( mRunning )
		{
			auto current_state = MqttStateMachine::current_state_ptr;
			//std::cout << "Current State:" << current_state->GetStateName() << "\n";

			MqttStateMachine::dispatch( MqttEventCycle() );

			sleep(1);
		}
	}

protected:
	std::string mName;

	static MosquittoVisitor* mClient;
	static bool mRunning;
	static bool mShutdown;
};
