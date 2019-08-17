#pragma once

#include "Generic.h"
#include "IParameter.h"

#include "designpatterns/Composite.h"

/**
 *  Interface: IActuator
 */
class IActuator:
        public Generic,
        public Composite< IParameter >
{

};
