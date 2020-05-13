#pragma once 

#include "tinyfsm.hpp"
#include <iostream>
#include <string>

// StateMachine Events
struct MqttEventConnect : tinyfsm::Event { };
struct MqttEventDisconnect : tinyfsm::Event { };
struct MqttEventTerminate : tinyfsm::Event { };

// Base StateMachine
class MqttStateMachine
	:public tinyfsm::Fsm< MqttStateMachine >
{
public:
	MqttStateMachine& operator=( const MqttStateMachine & other ) 
	{
		std::cout << "MqttStateMachine: Copy\n";
		return *this;
	}

	virtual void entry( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[OnEntry]\n";
	}

	virtual void cycle( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[Cycle]\n";
	}

	virtual void exit( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[OnExit]\n";
	}

	static void reset( void );

	/* Events */
	virtual void react( MqttEventConnect const & ){};
	virtual void react( MqttEventDisconnect const & ){};
	virtual void react( MqttEventTerminate const & ){};

};

