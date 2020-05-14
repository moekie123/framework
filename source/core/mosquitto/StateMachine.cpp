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

	// Doxygen Transit{ MqttStateIdle -> MqttStateIdle [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mShutdown )
			mRunning = false;
	}		

	// Doxygen Transit{ MqttStateIdle -> MqttStateIdle [label="eTerminate"] }
	void react( eTerminate const & )
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
	// Doxygen Transit{ MqttStateInitializing -> MqttStateInitializing [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitInitialize( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateInitializing -> MqttStateConfiguring [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateConfiguring >(); 
	};

	// Doxygen Transit{ MqttStateInitializing -> MqttStateCleanup [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateInitializing -> MqttStateCleanup [label="eTerminate"] }
	void react( eTerminate const & )
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

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateConfiguring [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitConfigure( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateConnecting [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateConnecting >(); 
	};

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateDestroy [label="eDestroy"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateConfiguring -> MqttStateDestroy [label="eTerminate"] }
	void react( eTerminate const & )
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

	// Doxygen Transit{ MqttStateConnecting -> MqttStateConnecting [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitConnect( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateConnecting -> MqttStateListening [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateListening >(); 
	};

	// Doxygen Transit{ MqttStateConnecting -> MqttStateDestroy [label="eDestroy"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateConnecting -> MqttStateDestroy [label="eTerminate"] }
	void react( eTerminate const & )
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

	// Doxygen Transit{ MqttStateListening -> MqttStateListening [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitLoop( *this ) )
		{

		}
	}

	// Doxygen Transit{ MqttStateListening -> MqttStateDisconnecting [label="eTerminate"] }
	void react( eTerminate const & )
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
	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDisconnecting [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitDisconnect( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDestroy [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDisconnecting [label="eFailure"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateDisconnecting >(); 
	};

	// Doxygen Transit{ MqttStateDisconnecting -> MqttStateDestroy [label="eTerminate"] }
	void react( eTerminate const & )
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
	// Doxygen Transit{ MqttStateDestroy -> MqttStateDestroy [label="eCycle"] }
	void react( eCycle const & )
	{

		if( mClient->visitDestroy( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateDestroy -> MqttStateCleanup [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateDestroy -> MqttStateDestroy [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateDestroy >(); 
	};

	// Doxygen Transit{ MqttStateDestroy -> MqttStateCleanup [label="eTerminate"] }
	void react( eTerminate const & )
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
	// Doxygen Transit{ MqttStateCleanup -> MqttStateCleanup [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitCleanup( *this ) )
		{
			MqttStateMachine::dispatch( eSucces() );
		}
		else
		{
			MqttStateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< MqttStateIdle >(); 
	};

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< MqttStateCleanup >(); 
	};

	// Doxygen Transit{ MqttStateCleanup -> MqttStateIdle [label="eTerminate"] }
	void react( eTerminate const & )
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

