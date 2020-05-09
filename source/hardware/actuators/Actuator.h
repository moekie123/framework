#pragma once

#include "IActuator.h"

#include "Builder.h"
#include "Singleton.h"
#include "Factory.h"

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
	 * @brief The Actutor Builder Class to create new (base) Actuators
	 */
	class ActuatorBuilder:
		public Builder
	{
		public:
		Generic* Build( std::string _name ) override
		{
			Factory& factory = Singleton< Factory >::Instance();
			//auto config = factory.Create< IConfigurator >( "Configurator", _name );

			Actuator* actuator = new Actuator( _name );

			std::string parameters[] = 
			{ 
				"/config/refresh",
				"/config/log",
				"/config/mode",
				"/config/stepsize",
				"/config/period",
				"/config/profile",
			};

			for( auto& parameter: parameters )
			{
				auto p = factory.Create< IParameter >( "Parameter", _name + parameter );
				actuator->Add( p );
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
    	Actuator( std::string _name );
};
