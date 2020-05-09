#include "Actuator.h"

#include "Singleton.h"
#include "Factory.h"

#include "IConfigurator.h"
#include "IParameter.h"

#include <string>
#include <iostream>

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( std::string _name ) 
{
    	mName = _name;
}
