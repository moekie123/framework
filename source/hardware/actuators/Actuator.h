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
#include "StateMachine.h"

// Stl-Headers
#include <vector>
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

                        // Retrieve Factory
		        auto factory = Singleton<Factories>::Instance();

                        // Get mosquito client
                        auto mosquitto = factory.Construct<IMosquitto>( "Mosquitto", "mosquitto" );

                        // Createe new Actuator
                        Actuator* actuator = new Actuator( *_config, _name );
                        _config->GetProperty( "Actuator", _name, "channels", channels );

                        // Add Channels to the actuator
                        for ( int index = 0; index < channels; index++ )
                        {
                                spdlog::info( "Configure Channels [{}]", index );

                                Channel* channel = new Channel( _config, _name + "/ch" + std::to_string( index ) );

                                mosquitto->Attach( *channel );
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
        bool visitInitialize( const ActuatorStateMachine& ) override;
        bool visitPreConfigure( const ActuatorStateMachine& ) override;
        bool visitConnect( const ActuatorStateMachine& ) override;
        bool visitPostConfigure( const ActuatorStateMachine& ) override;
        bool visitLoop( const ActuatorStateMachine& ) override;
        bool visitReconnect( const ActuatorStateMachine& ) override;
        bool visitDisconnect( const ActuatorStateMachine& ) override;
        bool visitDestroy( const ActuatorStateMachine& ) override;
        bool visitCleanup( const ActuatorStateMachine& ) override;

       private:
        std::string mDriver;
        std::string mChip;
};
