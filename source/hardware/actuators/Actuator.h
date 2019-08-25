#pragma once

#include "IActuator.h"

#include "Builder.h"
#include "Singleton.h"

#include <string>

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
		Generic* build( std::string _name ) override
		{
			//Factory& factory = Singleton< Factory >::Instance();
			//auto config = factory.Create< IConfigurator >( "Configurator", "configuration.xml" );
			return new Actuator( _name );
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
