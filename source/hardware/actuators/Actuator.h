#pragma once

#include "IActuator.h"

#include <string>
#include <vector>

class Actuator: 
    public IActuator
{
    public:
        Actuator( std::string _name );

};
