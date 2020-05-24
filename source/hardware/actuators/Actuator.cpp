// Inheritance
#include "Actuator.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"

// Stl-Headers
#include <iostream>
#include <string>

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( std::string _name )
{
        mName = _name;
}
