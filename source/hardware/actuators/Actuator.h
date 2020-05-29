#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IActuator.h"
#include "IParameter.h"

// ???
#include "Channel.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"
#include "Singleton.h"

// Stl-Headers
#include <string>

/**
 * @brief The (base) Actuator class
 */
class Actuator : public IActuator
{
       public:
        /**
	 * @brief The Actuator Builder Class to create new (base) Actuators
	 */
        class ActuatorBuilder : public Builder<IActuator>
        {
               public:
                /**
	 	 * @brief The constructor will map the Build-Method to the (base) Builder class
		 */
                ActuatorBuilder() : Builder( Build )
                {
                }

                /**
		 * @brief The build method that configures and constructs a new Parameter
		 * @param _config The pre build Configurator
		 * @param _name The name of the new Actuator
 		 */
                static IActuator* Build( const IConfigurator* _config, const std::string& _name )
                {
                        int channels = 0;

                        Actuator* actuator = new Actuator( *_config, _name );

                        _config->GetProperty( "Actuator", _name, "channels", channels );

                        for ( int index = 0; index < channels; index++ )
                        {
                                spdlog::info( "Configure Channels [{}]", index );

                                Channel* channel = new Channel( _config, std::to_string( index ) );
                                actuator->Add( *channel );
                        }

                        return actuator;
                }
        };

        /**
	 * @brief The global Actuator builder that can be registerd to a (abstract) Factory
	 */
        static ActuatorBuilder builder;

        /**
	 * @brief The base constructor
	 * @param _name The name of the actuartor
	 */
        Actuator( const IConfigurator& _config, std::string _name );

        /**
	 * @brief Enable/Disable the channels of the chip
	 * @param _enable True; Enable the channels
	 * @return The amount of channels that are enabled/disableld
	 */
        int Channels( bool _enable );

        /** 
	 * Visitor Pattern Methods
	 */
        bool visitInitialize( const StateMachine& ) override;
        bool visitPreConfigure( const StateMachine& ) override;
        bool visitConnect( const StateMachine& ) override;
        bool visitPostConfigure( const StateMachine& ) override;
        bool visitLoop( const StateMachine& ) override;
        bool visitReconnect( const StateMachine& ) override;
        bool visitDisconnect( const StateMachine& ) override;
        bool visitDestroy( const StateMachine& ) override;
        bool visitCleanup( const StateMachine& ) override;

       private:
        std::string mDriver;
        std::string mChip;
};
