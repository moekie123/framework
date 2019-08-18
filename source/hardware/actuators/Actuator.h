#pragma once

#include "IActuator.h"

#include "designpatterns/Builder.h"
#include "designpatterns/Singleton.h"

#include <string>

class Actuator: 
    public IActuator
{
    public:
	/**
	 * Builder
	 */
	class ActuatorBuilder:
		public Builder
	{
		public:
		Generic* build( std::string _name ) override
		{
			return new Actuator( _name );
		}
	};
	static ActuatorBuilder builder;
	
    	Actuator( std::string _name );
};
