#pragma once

#include "Generic.h"

#include "Subject.h"
#include "IParameter.h"

// Forward declaration
class IParameter;

/** 
 * @brief The Mosquitto Interface
 * @details Note that only Parameters are allowed to attach to the broker
 */
class IMosquitto:
	public Generic,
	public Subject< IParameter >
{


};
