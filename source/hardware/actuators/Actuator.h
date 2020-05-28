#pragma once

// Interfaces
#include "IActuator.h"
#include "IParameter.h"

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
                        Factories& factory = Singleton<Factories>::Instance();

                        Actuator* actuator = new Actuator( *_config, _name );

                        const std::string parameters[] = {
                                "config/refresh",
                                "config/log",
                                "config/mode",
                                "config/stepsize",
                                "config/period",
                                "config/profile",
                        };

                        for ( const std::string& parameter : parameters )
                        {
                                IParameter* p = factory.Construct<IParameter>( "Parameter", parameter );
                                actuator->Add( *p );
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
