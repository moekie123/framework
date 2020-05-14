#include "StateMachine.h"

// Declaring static variables
bool MqttStateMachine::mRunning = false;
bool MqttStateMachine::mShutdown = false;

MosquittoVisitor* MqttStateMachine::mClient;

// Forward Declaration
class MqttStateIdle;

class MqttStateInitializing;
class MqttStateConfiguring;
class MqttStateConnecting;

class MqttStateListening;

class MqttStateDisconnecting;
class MqttStateDestroy;
class MqttStateCleanup;

class MqttStateIdle:
	public MqttStateMachine
{
	public:
	MqttStateIdle():MqttStateMachine("Idle"){ }

	private:

	// Doxygen Transit{ MqttStateIdle -> MqttStateIdle [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mShutdown )
			mRunning = false;
	}		

	// Doxygen Transit{ MqttStateIdle -> MqttStateIdle [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
	};
};


class MqttStateInitializing:
	public MqttStateMachine
{
	public:
	MqttStateInitializing():MqttStateMachine("Initializing"){ }

	private:
	// Doxygen Transit{ MqttStateInitializing -> MqttStateInitializing [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitInitialize( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateInitializing -> MqttStateConfiguring [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateConfiguring >(); 
	};

	// Doxygen Transit{ MqttStateInitializing -> MqttStateCleanup [label="MqttEventFailed"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateInitializing -> MqttStateCleanup [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateCleanup >();
	};
};

class MqttStateConfiguring:
	public MqttStateMachine
{
	public:
	MqttStateConfiguring():MqttStateMachine("Configuring"){ }

	private:

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateConfiguring [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitConfigure( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateConnecting [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateConnecting >(); 
	};

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateDestroy [label="MqttEventDestroy"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateDestroy [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateDestroy >();
	};
};

class MqttStateConnecting:
	public MqttStateMachine
{
	public:
	MqttStateConnecting():MqttStateMachine("Connecting"){ }

	private:

	// Doxygen Transit{ MqttStateConnecting -> MqttStateConnecting [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitConnect( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateConnecting -> MqttStateListening [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateListening >(); 
	};

	// Doxygen Transit{ MqttStateConnecting -> MqttStateDestroy [label="MqttEventDestroy"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateConnecting -> MqttStateDestroy [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateDestroy >();
	};
};

class MqttStateListening:
	public MqttStateMachine
{
	public:
	MqttStateListening():MqttStateMachine("Listening"){ }

	private:

	// Doxygen Transit{ MqttStateListening -> MqttStateListening [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitLoop( *this ) )
		{

		}
	}

	// Doxygen Transit{ MqttStateListening -> MqttStateDisconnecting [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateDisconnecting >();
	};
};

class MqttStateDisconnecting:
	public MqttStateMachine
{
	public:
	MqttStateDisconnecting():MqttStateMachine("Disconnecting"){ }

	private:
	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDisconnecting [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitDisconnect( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDestroy [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDisconnecting [label="MqttEventFailure"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateDisconnecting >(); 
	};

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDestroy [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateDestroy >();
	};
};

class MqttStateDestroy:
	public MqttStateMachine
{
	public:
	MqttStateDestroy():MqttStateMachine("Destroying"){ }

	private:
	// Doxygen Transit{ MqttStateDestroy -> MqttStateDestroy [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{

		if( mClient->visitDestroy( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateDestroy -> MqttStateCleanup [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateDestroy -> MqttStateDestroy [label="MqttEventFailed"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateDestroy -> MqttStateCleanup [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true;
		transit< MqttStateCleanup >();
	};
};

class MqttStateCleanup:
	public MqttStateMachine
{
	public:
	MqttStateCleanup():MqttStateMachine("CleaningUp"){ }

	private:
	// Doxygen Transit{ MqttStateCleanup -> MqttStateCleanup [label="MqttEventCycle"] }
	void react( MqttEventCycle const & )
	{
		if( mClient->visitCleanup( *this ) )
		{
			MqttStateMachine::dispatch( MqttEventSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( MqttEventFailed() );
		}
	}

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="MqttEventSucces"] }
	void react( MqttEventSucces const & )
	{ 
		transit< MqttStateIdle >(); 
	};

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="MqttEventFailed"] }
	void react( MqttEventFailed const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="MqttEventTerminate"] }
	void react( MqttEventTerminate const & )
	{
		mShutdown = true; 
		transit< MqttStateIdle >();
	};
};

/* 
 * Use Idle as intial state when dispatch from outside is possible 
 * For now (development phase) immedially start with initializing
 */
//FSM_INITIAL_STATE( MqttStateMachine, MqttStateIdle )
FSM_INITIAL_STATE( MqttStateMachine, MqttStateInitializing )

