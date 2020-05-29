#pragma once

// Design Pattern
#include "Visitor.h"

// Third-Party
#include <spdlog/spdlog.h>
#include "tinyfsm.hpp"

// Stl-Headers
#include <string>

// Forward Declaration
template <int inum>
class Visitor;

// ########## StateMachine Events ##########

/** 
 * @brief The Cycle Event,
 * @details This event gets evoked on interval base
 */
struct eCycle : tinyfsm::Event
{
};

/**
  * @brief The Succes Event
  * @details This event gets evoked when the Visited Method returns true
  */
struct eSucces : tinyfsm::Event
{
};

/** 
  * @brief The Failed Event
  * @details This events gets evoked when the Visited Method returns false
  */
struct eFailed : tinyfsm::Event
{
};

/** 
  * @brief The Terminate Event
  * @details This events gets evoked when a exteranl signal tries to shutdown the StateMachine
  */
struct eTerminate : tinyfsm::Event
{
};

// ########## StateMachine Base ##########

/**
 * @brief The (Base) Statemachine Class
 * @details This class holds the basics for a state in the StateMachine
 */
template <int inum>
class StateMachine
    : public tinyfsm::Fsm<StateMachine<inum>>
{
       public:
        /**
	 * @brief The Constructor
	 * @details This is used to create a new State, and give it a new
	 * @param _name The name of the new state
	 */
        StateMachine( std::string _name ) : mName( _name )
        {
        }

        /**
	 * @brief OnEntry
	 * @details This method gets called everytime the StateMachine enters a new state
 	 */
        virtual void entry( void )
        {
                spdlog::trace( "StateMachine: S[{}] E[OnEntry]", mName );
        }

        /**
	 * @brief OnExit
	 * @details This method gets called everytime the StateMachine exits a new state
	 */
        virtual void exit( void )
        {
                spdlog::trace( "StateMachine: S[{}] E[OnExit]", mName );
        }

        /* Events */

        /** 
	 * @brief StateMachine reaction on a eCycle Event
	 * @param e The event that got triggered
	 */
        virtual void react( eCycle const &e ){};

        /** 
	 * @brief StateMachine reaction on a eSucces Event 
	 * @param e The event that got triggered
	 */
        virtual void react( eSucces const &e ){};

        /** 
	 * @brief StateMachine reaction on a eFailed Event 
	 * @param e The event that got triggered
	 */
        virtual void react( eFailed const &e ){};

        /** 
	 * @brief StateMachine reaction on a eTerminate Event 
	 * @param e The event that got triggered
 	*/
        virtual void react( eTerminate const &e ){};

        /**
	 * @brief Getter
	 * @return The stringbased name of the state
 	 */
        const std::string &GetStateName()
        {
                return mName;
        }

        /**
	 * @brief Active State
	 * @return Whether the Statemachine is still running
 	 */
        static bool IsRunning()
        {
                return mRunning;
        }

        /**
	 * @brief (Visitor Pattern) This accept(or) part of visitor pattern.
	 * @details This method will start the StateMachine and will stay here untill the StateMachine is cancelled
 	 */
        static void Accept( Visitor<inum> &_visitor )
        {
                spdlog::debug( "Vistor Accepted" );

                mClient = &_visitor;

                //                StateMachine<inum>::start();

                mRunning = true;
        }

       protected:
        /**
	 * @brief The name of the state
	 * TODO: This can be replaced by a PRETTY_FUNCTION
	 */
        std::string mName;

        /**
	 * @brief The Visitor Client 
	 * @details The visitable part in the vistor pattern
	 */
        static Visitor<inum> *mClient;

        /**
	 * @brief The state of the StateMachien
	 * @details Whether the StateMachine is active(True) or not (False)
	 */
        static bool mRunning;

        /** 
	 * @brief The flag that will try to exit the statemachine
	 * @details This flag can be set by sending a eTerminate event from outside the StateMachine
	 */
        static bool mShutdown;
};

using MqttStateMachine = StateMachine<0>;
using ActuatorStateMachine = StateMachine<1>;

using StateMachines = tinyfsm::FsmList<
    MqttStateMachine,
    ActuatorStateMachine>;

