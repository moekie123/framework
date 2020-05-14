#include "StateMachine.h"

// Declaring static variables
bool StateMachine::mRunning = false;
bool StateMachine::mShutdown = false;

MosquittoVisitor* StateMachine::mClient;

// Forward Declaration
class sIdle;

class sInitializing;
class sConfiguring;
class sConnecting;

class sListening;

class sDisconnecting;
class sDestroy;
class sCleanup;

class sIdle:
	public StateMachine
{
	public:
	sIdle():StateMachine("Idle"){ }

	private:

	// Doxygen Transit{ sIdle -> sIdle [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mShutdown )
			mRunning = false;
	}		

	// Doxygen Transit{ sIdle -> sIdle [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
	};
};


class sInitializing:
	public StateMachine
{
	public:
	sInitializing():StateMachine("Initializing"){ }

	private:
	// Doxygen Transit{ sInitializing -> sInitializing [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitInitialize( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sInitializing -> sConfiguring [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sConfiguring >(); 
	};

	// Doxygen Transit{ sInitializing -> sCleanup [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< sCleanup >(); 
	};

	// Doxygen Transit{ sInitializing -> sCleanup [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sCleanup >();
	};
};

class sConfiguring:
	public StateMachine
{
	public:
	sConfiguring():StateMachine("Configuring"){ }

	private:

	// Doxygen Transit{ sConfiguring -> sConfiguring [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitConfigure( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sConfiguring -> sConnecting [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sConnecting >(); 
	};

	// Doxygen Transit{ sConfiguring -> sDestroy [label="eDestroy"] }
	void react( eFailed const & )
	{ 
		transit< sDestroy >(); 
	};

	// Doxygen Transit{ sConfiguring -> sDestroy [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sDestroy >();
	};
};

class sConnecting:
	public StateMachine
{
	public:
	sConnecting():StateMachine("Connecting"){ }

	private:

	// Doxygen Transit{ sConnecting -> sConnecting [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitConnect( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sConnecting -> sListening [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sListening >(); 
	};

	// Doxygen Transit{ sConnecting -> sDestroy [label="eDestroy"] }
	void react( eFailed const & )
	{ 
		transit< sDestroy >(); 
	};

	// Doxygen Transit{ sConnecting -> sDestroy [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sDestroy >();
	};
};

class sListening:
	public StateMachine
{
	public:
	sListening():StateMachine("Listening"){ }

	private:

	// Doxygen Transit{ sListening -> sListening [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitLoop( *this ) )
		{

		}
	}

	// Doxygen Transit{ sListening -> sDisconnecting [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sDisconnecting >();
	};
};

class sDisconnecting:
	public StateMachine
{
	public:
	sDisconnecting():StateMachine("Disconnecting"){ }

	private:
	// Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitDisconnect( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sDisconnecting -> sDestroy [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sDestroy >(); 
	};

	// Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eFailure"] }
	void react( eFailed const & )
	{ 
		transit< sDisconnecting >(); 
	};

	// Doxygen Transit{ sDisconnecting -> sDestroy [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sDestroy >();
	};
};

class sDestroy:
	public StateMachine
{
	public:
	sDestroy():StateMachine("Destroying"){ }

	private:
	// Doxygen Transit{ sDestroy -> sDestroy [label="eCycle"] }
	void react( eCycle const & )
	{

		if( mClient->visitDestroy( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sDestroy -> sCleanup [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sCleanup >(); 
	};

	// Doxygen Transit{ sDestroy -> sDestroy [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< sDestroy >(); 
	};

	// Doxygen Transit{ sDestroy -> sCleanup [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true;
		transit< sCleanup >();
	};
};

class sCleanup:
	public StateMachine
{
	public:
	sCleanup():StateMachine("CleaningUp"){ }

	private:
	// Doxygen Transit{ sCleanup -> sCleanup [label="eCycle"] }
	void react( eCycle const & )
	{
		if( mClient->visitCleanup( *this ) )
		{
			StateMachine::dispatch( eSucces() );
		}
		else
		{
			StateMachine::dispatch( eFailed() );
		}
	}

	// Doxygen Transit{ sCleanup -> sIdle [label="eSucces"] }
	void react( eSucces const & )
	{ 
		transit< sIdle >(); 
	};

	// Doxygen Transit{ sCleanup -> sIdle [label="eFailed"] }
	void react( eFailed const & )
	{ 
		transit< sCleanup >(); 
	};

	// Doxygen Transit{ sCleanup -> sIdle [label="eTerminate"] }
	void react( eTerminate const & )
	{
		mShutdown = true; 
		transit< sIdle >();
	};
};

/* 
 * Use Idle as intial state when dispatch from outside is possible 
 * For now (development phase) immedially start with initializing
 */
//FSM_INITIAL_STATE( StateMachine, sIdle )
FSM_INITIAL_STATE( StateMachine, sInitializing )

