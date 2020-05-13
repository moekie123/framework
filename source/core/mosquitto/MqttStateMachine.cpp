#include "MqttStateMachine.h"

// Define State
class MqttStateInitialized;
class MqttStateTerminated;
class MqttStateDisconnected;
class MqttStateConnected;

class MqttStateInitialized:
	public MqttStateMachine
{
	void entry( void ) override
	{
		std::cout << "MqttStateMachine: S[Initialized] E[Entry]\n";
		std::cout << "MqttStateMachine:	Initializing\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[Initialized] E[Cycle]\n";

		// Ready with with initializing and detected that the client is disconnected
		MqttStateMachine::dispatch( MqttEventDisconnect() );
	}

	void react( MqttEventDisconnect const & )
	{
		std::cout << "MqttStateMachine: S[Initialized] R[Disconnect]\n";
		transit< MqttStateDisconnected >(); 
	};

};

class MqttStateTerminated:
	public MqttStateMachine
{
	void entry( void ) override
	{
		std::cout << "MqttStateMachine: S[Terminated] E[Entry]\n";
		std::cout << "MqttStateMachine:	Terminating\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[Terminated] E[Cycle]\n";
	}
};


class MqttStateDisconnected:
	public MqttStateMachine
{
	void entry( void ) override
	{
		std::cout << "MqttStateMachine: S[Disconnected] E[Entry]\n";
		std::cout << "MqttStateMachine: Disconnecting\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[Disconnected] E[Cycle]\n";
		MqttStateMachine::dispatch( MqttEventConnect() );
//		MqttStateMachine::dispatch( MqttEventTerminate() );
	}

	virtual void react( MqttEventConnect const & )
	{
		std::cout << "MqttStateMachine: S[Disconnected] R[Connect]\n";
		transit< MqttStateConnected >(); 
	};

	virtual void react( MqttEventTerminate const & )
	{
		std::cout << "MqttStateMachine: S[Disconnected] R[Terminate]\n";
		transit< MqttStateConnected >(); 
	};

	void exit( void ) override
	{
		std::cout << "MqttStateMachine: S[Disconnected] E[Exit]\n";
	}
};

class MqttStateConnected:
	public MqttStateMachine
{
	void entry( void ) override
	{
		std::cout << "MqttStateMachine: S[Connected] E[Entry]\n";
		std::cout << "MqttStateMachine: Connecting\n";
	}

	void cycle( void ) override
	{
		std::cout << "MqttStateMachine: S[Connected] E[Cycle]\n";
	}

	virtual void react( MqttEventDisconnect const & )
	{
		std::cout << "MqttStateMachine: S[Connected] R[Disconnect]\n";
		transit< MqttStateDisconnected >(); 
	};
};

FSM_INITIAL_STATE( MqttStateMachine, MqttStateInitialized )

