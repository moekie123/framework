// Inheritance
#include "StateMachine.h"

// Declaring static variables
template <int inum>
bool StateMachine<inum>::mRunning = false;

template <int inum>
bool StateMachine<inum>::mShutdown = false;

template <int inum>
Visitor<inum>* StateMachine<inum>::mClient;

// (Forward) State Declaration
template <int inum>
class sIdle;

template <int inum>
class sInitializing;

template <int inum>
class sPreConfiguring;

template <int inum>
class sConnecting;

template <int inum>
class sPostConfiguring;

template <int inum>
class sListening;

template <int inum>
class sDisconnecting;

template <int inum>
class sDestroy;

template <int inum>
class sCleanup;

/** 
 *  @brief The Idle State
 *  @details From this State the StateMachine can exit
 */
template <int inum>
class sIdle : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sIdle() : base( "Idle" ) {}

       private:
        // Doxygen Transit{ sIdle -> sIdle [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mShutdown )
                        base::mRunning = false;
        }

        // Doxygen Transit{ sIdle -> sIdle [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
        };
};

/** 
 *  @brief The Initializing State
 *  @details From this State the StateMachine will call the Mosquito Client to intialize by visiting 'Mosquitto::visitInitialize'
 */
template <int inum>
class sInitializing : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sInitializing() : base( "Initializing" ) {}

       private:
        // Doxygen Transit{ sInitializing -> sInitializing [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitInitialize( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sInitializing -> sPreConfiguring [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sPreConfiguring<inum>>();
        };

        // Doxygen Transit{ sInitializing -> sCleanup [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sCleanup<inum>>();
        };

        // Doxygen Transit{ sInitializing -> sCleanup [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sCleanup<inum>>();
        };
};

/** 
 *  @brief The Configuring State
 *  @details From this State the StateMachine will call the Mosquito Client to configure, by visiting 'Mosquitto::visitConfigure'
 */
template <int inum>
class sPreConfiguring : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sPreConfiguring() : base( "PreConfiguring" ) {}

       private:
        // Doxygen Transit{ sPreConfiguring -> sPreConfiguring [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitPreConfigure( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sPreConfiguring -> sConnecting [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sConnecting<inum>>();
        };

        // Doxygen Transit{ sPreConfiguring -> sDestroy [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sDestroy<inum>>();
        };

        // Doxygen Transit{ sPreConfiguring -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sDestroy<inum>>();
        };
};

/** 
 *  @brief The Connecting State
 *  @details From this State the StateMachine will call the Mosquito Client to connect, by visiting 'Mosquitto::visitConnect'
 */
template <int inum>
class sConnecting : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sConnecting() : base( "Connecting" ) {}

       private:
        // Doxygen Transit{ sConnecting -> sConnecting [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitConnect( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sConnecting -> sListening [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sPostConfiguring<inum>>();
        };

        // Doxygen Transit{ sConnecting -> sDestroy [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sDestroy<inum>>();
        };

        // Doxygen Transit{ sConnecting -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sDestroy<inum>>();
        };
};

/** 
 *  @brief The PreConfiguring State
 */
template <int inum>
class sPostConfiguring : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sPostConfiguring() : base( "PostConfiguring" ) {}

       private:
        // Doxygen Transit{ sPostConfiguring -> sPostConfiguring [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitPostConfigure( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sPostConfiguring -> sListing [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sListening<inum>>();
        };

        // Doxygen Transit{ sPostConfiguring -> sDisconnecting [label="eDestroy"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sDisconnecting<inum>>();
        };

        // Doxygen Transit{ sPostConfiguring -> sDisconnecting [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sDisconnecting<inum>>();
        };
};

/** 
 *  @brief The Listening State
 *  @details From this State the StateMachine will call the Mosquito Client to listen for new messages, by visiting 'Mosquitto::visitLoop'
 */
template <int inum>
class sListening : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sListening() : base( "Listening" ) {}

       private:
        // Doxygen Transit{ sListening -> sListening [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitLoop( *this ) == false )
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sListening -> sDisconnecting [label="eTerminate"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::mShutdown = true;
                base::template transit<sDisconnecting<inum>>();
        };

        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sDisconnecting<inum>>();
        };
};

/** 
 *  @brief The Disconnecting State
 *  @details From this State the StateMachine will call the Mosquito Client to disconnect, by visiting 'Mosquitto::visitDisconnect'
 */
template <int inum>
class sDisconnecting : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sDisconnecting() : base( "Disconnecting" ) {}

       private:
        // Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitDisconnect( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sDisconnecting -> sDestroy [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sDestroy<inum>>();
        };

        // Doxygen Transit{ sDisconnecting -> sDisconnecting [label="eFailure"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sDisconnecting<inum>>();
        };

        // Doxygen Transit{ sDisconnecting -> sDestroy [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sDestroy<inum>>();
        };
};

/** 
 *  @brief The Destroy State
 *  @details From this State the StateMachine will call the Mosquito Client to destroy, by visiting 'Mosquitto::visitDestroy'
 */
template <int inum>
class sDestroy : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sDestroy() : base( "Destroying" ) {}

       private:
        // Doxygen Transit{ sDestroy -> sDestroy [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitDestroy( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sDestroy -> sCleanup [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sCleanup<inum>>();
        };

        // Doxygen Transit{ sDestroy -> sDestroy [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sDestroy<inum>>();
        };

        // Doxygen Transit{ sDestroy -> sCleanup [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sCleanup<inum>>();
        };
};

/** 
 *  @brief The Cleanup State
 *  @details From this State the StateMachine will call the Mosquito Client to clean up, by visiting 'Mosquitto::visitCleanup'
 */
template <int inum>
class sCleanup : public StateMachine<inum>
{
        using base = StateMachine<inum>;

       public:
        sCleanup() : base( "CleaningUp" ) {}

       private:
        // Doxygen Transit{ sCleanup -> sCleanup [label="eCycle"] }
        void react( eCycle const& )
        {
                if ( base::mClient->visitCleanup( *this ) )
                {
                        base::dispatch( eSucces() );
                }
                else
                {
                        base::dispatch( eFailed() );
                }
        }

        // Doxygen Transit{ sCleanup -> sIdle [label="eSucces"] }
        void react( eSucces const& )
        {
                spdlog::debug( "Event [eSucces]" );
                base::template transit<sIdle<inum>>();
        };

        // Doxygen Transit{ sCleanup -> sIdle [label="eFailed"] }
        void react( eFailed const& )
        {
                spdlog::debug( "Event [eFailed]" );
                base::template transit<sCleanup<inum>>();
        };

        // Doxygen Transit{ sCleanup -> sIdle [label="eTerminate"] }
        void react( eTerminate const& )
        {
                spdlog::debug( "Event [eTerminate]" );
                base::mShutdown = true;
                base::template transit<sIdle<inum>>();
        };
};

/* 
 * Use Idle as intial state when dispatch from outside is possible 
 * For now (development phase) immedially start with initializing
 */
//FSM_INITIAL_STATE( StateMachine, sIdle )
FSM_INITIAL_STATE( StateMachine<0>, sInitializing<0> )
FSM_INITIAL_STATE( StateMachine<1>, sInitializing<1> )

