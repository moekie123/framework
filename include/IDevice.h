#pragma once

#include "Generic.h"
#include "IParameter.h"
#include "Composite.h"
#include <stdexcept>

/**
 * @brief The generic interface class for an Device
 */
class IDevice:

//	public Generic,
	public Composite< IParameter >
{
	public:

		/**
		 * @brief Set the value of the device
		 * @details TODO: This can be replaced for the Generic version
		 * @details (On purpose) This method is not abstract because otherwise it could be generarated by the Factory
		 * @return Throws exception when not implemented
		 */
		virtual void Set( const std::string&, int ) 
		{
			throw std::logic_error("Not Implemented");
		}
};
