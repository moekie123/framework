#pragma once

#include "Generic.h"

#include "Subject.h"
#include "IParameter.h"

class IMosquitto:
	public Generic,
	public Subject< IParameter >
{


};
