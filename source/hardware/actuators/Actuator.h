#pragma once

#include "IActuator.h"
#include "IParameter.h"

#include "Builder.h"
#include "Singleton.h"

#include "AbstractFactory.h"
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
		public Builder< IActuator >
	{
		public:
		static IActuator* BuildActuator( const std::string _name )
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
//				IParameter& p = factory.Construct< IParameter >( "Parameter", _name + parameter );
				actuator->Add( *p );
			}
			
			return actuator;
		}

		ActuatorBuilder(): Builder( BuildActuator )
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
