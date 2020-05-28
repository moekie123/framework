// Inheritance
#include "StateMachine.h"

// Declaring static variables
bool StateMachine::mRunning = false;
bool StateMachine::mShutdown = false;

Visitor* StateMachine::mClient;

// (Forward) State Declaration
class sIdle;
class sInitializing;

class sPreConfiguring;
class sConnecting;
class sPostConfiguring;

class sListening;
class sDisconnecting;
class sDestroy;
class sCleanup;

/** 
 *  @brief The Idle State
 *  @details From this State the StateMachine can exit
 */
class sIdle : public StateMachine
{
       public:
        sIdle() : StateMachine( "Idle" ) {}

       private:
        // Doxygen Transit{ sIdle -> sIdle [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mShutdown )
                        mRunning = false;
        }

        // Doxygen Transit{ sIdle -> sIdle [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
        };
};

/** 
 *  @brief The Initializing State
 *  @details From this State the StateMachine will call the Mosquito Client to intialize by visiting 'Mosquitto::visitInitialize'
 */
class sInitializing : public StateMachine
{
       public:
        sInitializing() : StateMachine( "Initializing" ) {}

       private:
        // Doxygen Transit{ sInitializing -> sInitializing [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitInitialize( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sInitializing -> sPreConfiguring [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sPreConfiguring>();
        };

        // Doxygen Transit{ sInitializing -> sCleanup [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sCleanup>();
        };

        // Doxygen Transit{ sInitializing -> sCleanup [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sCleanup>();
        };
};

/** 
 *  @brief The Configuring State
 *  @details From this State the StateMachine will call the Mosquito Client to configure, by visiting 'Mosquitto::visitConfigure'
 */
class sPreConfiguring : public StateMachine
{
       public:
        sPreConfiguring() : StateMachine( "PreConfiguring" ) {}

       private:
        // Doxygen Transit{ sPreConfiguring -> sPreConfiguring [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitPreConfigure( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sPreConfiguring -> sConnecting [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sConnecting>();
        };

        // Doxygen Transit{ sPreConfiguring -> sDestroy [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sDestroy>();
        };

        // Doxygen Transit{ sPreConfiguring -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sDestroy>();
        };
};

/** 
 *  @brief The Connecting State
 *  @details From this State the StateMachine will call the Mosquito Client to connect, by visiting 'Mosquitto::visitConnect'
 */
class sConnecting : public StateMachine
{
       public:
        sConnecting() : StateMachine( "Connecting" ) {}

       private:
        // Doxygen Transit{ sConnecting -> sConnecting [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitConnect( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sConnecting -> sListening [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sPostConfiguring>();
        };

        // Doxygen Transit{ sConnecting -> sDestroy [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sDestroy>();
        };

        // Doxygen Transit{ sConnecting -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sDestroy>();
        };
};

/** 
 *  @brief The PreConfiguring State
 */
class sPostConfiguring : public StateMachine
{
       public:
        sPostConfiguring() : StateMachine( "PostConfiguring" ) {}

       private:
        // Doxygen Transit{ sPostConfiguring -> sPostConfiguring [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitPostConfigure( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sPostConfiguring -> sListing [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sListening>();
        };

        // Doxygen Transit{ sPostConfiguring -> sDisconnecting [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sDisconnecting>();
        };

        // Doxygen Transit{ sPostConfiguring -> sDisconnecting [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sDisconnecting>();
        };
};

/** 
 *  @brief The Listening State
 *  @details From this State the StateMachine will call the Mosquito Client to listen for new messages, by visiting 'Mosquitto::visitLoop'
 */
class sListening : public StateMachine
{
       public:
        sListening() : StateMachine( "Listening" ) {}

       private:
        // Doxygen Transit{ sListening -> sListening [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitLoop( *this ) == false )
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sListening -> sDisconnecting [label="eTerminate"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                mShutdown = true;
                transit<sDisconnecting>();
        };

        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sDisconnecting>();
        };
};

/** 
 *  @brief The Disconnecting State
 *  @details From this State the StateMachine will call the Mosquito Client to disconnect, by visiting 'Mosquitto::visitDisconnect'
 */
class sDisconnecting : public StateMachine
{
       public:
        sDisconnecting() : StateMachine( "Disconnecting" ) {}

       private:
        // Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitDisconnect( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sDisconnecting -> sDestroy [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sDestroy>();
        };

        // Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eFailure"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sDisconnecting>();
        };

        // Doxygen Transit{ sDisconnecting -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sDestroy>();
        };
};

/** 
 *  @brief The Destroy State
 *  @details From this State the StateMachine will call the Mosquito Client to destroy, by visiting 'Mosquitto::visitDestroy'
 */
class sDestroy : public StateMachine
{
       public:
        sDestroy() : StateMachine( "Destroying" ) {}

       private:
        // Doxygen Transit{ sDestroy -> sDestroy [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitDestroy( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sDestroy -> sCleanup [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sCleanup>();
        };

        // Doxygen Transit{ sDestroy -> sDestroy [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sDestroy>();
        };

        // Doxygen Transit{ sDestroy -> sCleanup [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sCleanup>();
        };
};

/** 
 *  @brief The Cleanup State
 *  @details From this State the StateMachine will call the Mosquito Client to clean up, by visiting 'Mosquitto::visitCleanup'
 */
class sCleanup : public StateMachine
{
       public:
        sCleanup() : StateMachine( "CleaningUp" ) {}

       private:
        // Doxygen Transit{ sCleanup -> sCleanup [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( mClient->visitCleanup( *this ) )
                {
                        StateMachine::dispatch( eSucces() );
                }
                else
                {
                        StateMachine::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sCleanup -> sIdle [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                transit<sIdle>();
        };

        // Doxygen Transit{ sCleanup -> sIdle [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                transit<sCleanup>();
        };

        // Doxygen Transit{ sCleanup -> sIdle [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                mShutdown = true;
                transit<sIdle>();
        };
};

/* 
 * Use Idle as intial state when dispatch from outside is possible 
 * For now (development phase) immedially start with initializing
 */
//FSM_INITIAL_STATE( StateMachine, sIdle )
FSM_INITIAL_STATE( StateMachine, sInitializing )
