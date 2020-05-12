#pragma once 

#include "tinyfsm.hpp"
#include <iostream>
#include <string>

// StateMachine Events
struct MqttEventInitialize : tinyfsm::Event 
{ 

};

struct MqttEventInitialized : tinyfsm::Event 
{ 

};

struct MqttEventTerminate : tinyfsm::Event 
{ 

};

struct MqttEventTerminated : tinyfsm::Event 
{ 

};

class MqttStateMachine
	:public tinyfsm::Fsm< MqttStateMachine >
{
public:
	MqttStateMachine& operator=( const MqttStateMachine & other ) 
	{
		std::cout << "MqttStateMachine: Copy\n";
		return *this;
	}

	void entry( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[OnEntry]\n";
	}

	virtual void cycle( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[Cycle]\n";
	}

	void exit( void )
	{
		std::cout << "MqttStateMachine: S[Base] E[OnExit]\n";
	}

	static void reset( void );

	/* Events */
	virtual void react( MqttEventInitialize const & ){};
	virtual void react( MqttEventInitialized const & ){};
	virtual void react( MqttEventTerminate const & ){};
	virtual void react( MqttEventTerminated const & ){};

};
// Define State

class MqttStateIdle;
class MqttStateInitializing; 
class MqttStateTerminating;
class MqttStateDisconnected;

class MqttStateIdle :
	public MqttStateMachine
{
	void react( MqttEventInitialize const &) override 
	{
 		std::cout << "MqttState: S[Idle] E[Initialize]\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[MqttStateIdle] E[Cycle]\n";
 		transit< MqttStateInitializing  >(); 
	}
};

class MqttStateInitializing : 
	public MqttStateMachine 
{
	void react( MqttEventInitialized const &) override 
	{
  		std::cout << "MqttState: S[Initializing] E[Initialized]\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[MqttStateInitializing] E[Cycle]\n";
 		transit< MqttStateDisconnected >(); 
	}

};

class MqttStateTerminating : 
	public MqttStateMachine
{
	void react( MqttEventTerminated const &) override 
	{
  		std::cout << "MqttState: S[Terminating] E[Terminated]\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[MqttStateTerminating] E[Cycle]\n";
 		transit< MqttStateIdle >(); 
	}

};

class MqttStateDisconnected : 
	public MqttStateMachine
{
	void react( MqttEventTerminate const &) override 
	{
  		std::cout << "MqttState: S[Disconnected] E[Terminate]\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[MqttStateTerminate] E[Cycle]\n";
	 	transit< MqttStateTerminating >(); 
	}

};

