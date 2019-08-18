#pragma once

#include "Generic.h"
#include "IParameter.h"
#include "Composite.h"

class IDevice:
	public Generic,
	public Composite< IDevice >,
	public Composite< IParameter >
{
	public:
		virtual void set( std::string, int ) = 0;
};
