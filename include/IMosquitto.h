#pragma once

#include "Generic.h"

#include "Subject.h"
#include "IParameter.h"

// Forward declaration
class IParameter;

class IMosquitto:
	public Generic,
	public Subject< IParameter >
{


};
