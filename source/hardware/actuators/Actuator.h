#pragma once

// Interfaces
#include "IActuator.h"
#include "IParameter.h"

// Design Patterns
#include "Builder.h"
#include "Singleton.h"
#include "AbstractFactory.h"
#include "Factory.h"

// Stl-Headers
#include <string>
#include <iostream>

/**
 * @brief The (base) Actuator class
 */
class Actuator: 
    public IActuator
{
    public:

   	/**
	 * @brief The Actuator Builder Class to create new (base) Actuators
	 */
	class ActuatorBuilder:
		public Builder< IActuator >
	{
	public:

		/**
		 * @brief The build method that configures and constructs a new Parameter
		 * @param _config The pre build Configurator
		 * @param _name The name of the new Actuator
 		 */
		static IActuator* Build( const IConfigurator* _config, const std::string& _name )
		{
			Factories& factory = Singleton< Factories >::Instance();

			Actuator* actuator = new Actuator( _name );

			const std::string parameters[] = 
			{ 
				"/config/refresh",
				"/config/log",
				"/config/mode",
				"/config/stepsize",
				"/config/period",
				"/config/profile",
			};

			for( const std::string& parameter: parameters )
			{
				IParameter* p = factory.Construct< IParameter >( "Parameter" );
				actuator->Add( *p );
			}
			
			return actuator;
		}

		/**
	 	 * @brief The constructor will map the Build-Method to the (base) Builder class
		 */
		ActuatorBuilder(): Builder( Build )
		{
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
    	Actuator( std::string _name );
};
