// Inheritance
#include "Actuator.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Singleton.h"
#include "Factory.h"

// Stl-Headers
#include <string>
#include <iostream>

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( std::string _name ) 
{
    	mName = _name;
}
