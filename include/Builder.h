#pragma once

#include "Generic.h"

#include <string>

/**
 * @Brief (Creational Design Pattern) Builder
 * @details A generic builder that can be attachted to a (Abstract)Factory pattern
 */
class Builder
{
	public:
		/**
		 * @brief build
		 * @details Generic method for all classed put in a Factory
		 */
		virtual Generic* build( std::string ) = 0;
};
