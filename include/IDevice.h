#pragma once

#include "Generic.h"
#include "IParameter.h"
#include "Composite.h"

/**
 * @brief The generic interface class for an Device
 */
class IDevice:
	public Generic,
	public Composite< IDevice >,
	public Composite< IParameter >
{
	public:

		/**
		 * @brief Set the value of the device
		 * @details TODO: This can be replaced for the Generic version
		 */
		virtual void set( std::string, int ) = 0;
};
