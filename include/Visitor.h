#pragma once

// Design Pattern
#include "StateMachine.h"

// Forward Declaration
class StateMachine;

/**
 * @brief (Visitor Pattern) The interface class for the Mosquitto class
 * @details This class contains all methods that the StateMachine is depending on as a Visitor
 * Check the state diagram of the StateMachine to see when each step is evoked
 */
class MosquittoVisitor
{
       public:
        /**
  		 * @brief The initializing step
                 * @details The Mosquitto client should start initializing the 'libmosquitto' when called
                 */
        virtual bool visitInitialize( const StateMachine& ) = 0;

        /**
  		 * @brief The configure step
                 * @details The Mosquitto client should start configuring when called
                 */
        virtual bool visitConfigure( const StateMachine& ) = 0;

        /**
  		 * @brief The connect step
                 * @details The Mosquitto client should start connecting when called
                 */
        virtual bool visitConnect( const StateMachine& ) = 0;

        /**
  		 * @brief The loop step
                 * @details The Mosquitto client should check for new messages when called
                 */
        virtual bool visitLoop( const StateMachine& ) = 0;

        /**
  		 * @brief The reconnect step
                 * @details The Mosquitto client should try to reconnect when called
                 */
        virtual bool visitReconnect( const StateMachine& ) = 0;

        /**
  		 * @brief The disconnect step
                 * @details The Mosquitto client should try to disconnect when called
                 */
        virtual bool visitDisconnect( const StateMachine& ) = 0;

        /**
  		 * @brief The destroy step
                 * @details The Mosquitto client should try to destroy/clear memory when called
                 */
        virtual bool visitDestroy( const StateMachine& ) = 0;

        /**
  		 * @brief The cleanup step
                 * @details The Mosquitto client should try to cleanup the 'libmosquitto' library
                 */
        virtual bool visitCleanup( const StateMachine& ) = 0;
};
