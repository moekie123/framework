#pragma once

#include "Generic.h"

#include <string>

/**
 * @brief The generic Builder that can be registerd in the (abstract) Factory.
 * @details This generic creational design pattern need to be inherent by a derived class to make registering in the abstract factory possible.
 */
class Builder
{
	public:
		/**
		 * @brief The build method will create a new derived class.
		 * @details 	This method should take care of all initliaztion and construction.
		 * 		The derived class should also inherent the Generic class.	
		 * @param _name The name of the new created derived class.
		 * @return The Generic class of the new created derived class.
		 */
		virtual Generic* Build( std::string _name ) = 0;
};
