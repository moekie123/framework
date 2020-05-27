#pragma once

// Design Pattern
#include "StateMachine.h"

// Forward Declaration
class StateMachine;

/**
 * @brief (Visitor Pattern) The interface class for the Statemachine
 * @details This class contains all methods that the StateMachine is depending on as a Visitor
 * Check the state diagram of the StateMachine to see when each step is evoked
 */
class Visitor
{
       public:
        /**
  		 * @brief The initializing step
                 * @details Here the instance should be initializeing
                 */
        virtual bool visitInitialize( const StateMachine& ) = 0;

        /**
  		 * @brief The configure step
                 * @details Here the instance is loaded in memory and should be configured
                 */
        virtual bool visitConfigure( const StateMachine& ) = 0;

        /**
  		 * @brief The connect step
                 * @details Here the insta instance will connect with the configuration
                 */
        virtual bool visitConnect( const StateMachine& ) = 0;

        /**
  		 * @brief The loop step
                 * @details Here the connection is enstablished
                 */
        virtual bool visitLoop( const StateMachine& ) = 0;

        /**
  		 * @brief The reconnect step
                 * @details Here the instance gets the opertunity to reconnect
                 */
        virtual bool visitReconnect( const StateMachine& ) = 0;

        /**
  		 * @brief The disconnect step
                 * @details Here the instance can gracefully disconnect
                 */
        virtual bool visitDisconnect( const StateMachine& ) = 0;

        /**
  		 * @brief The destroy step
                 * @details Here the instance will get rid of old configurations
                 */
        virtual bool visitDestroy( const StateMachine& ) = 0;

        /**
  		 * @brief The cleanup step
                 * @details Here the instance can be deleted
                 */
        virtual bool visitCleanup( const StateMachine& ) = 0;
};
