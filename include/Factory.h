#pragma once

// Design Patterns
#include "Builder.h"

// Stl-Headers
#include <map>
#include <string>

/**
 * @brief The (Base) Factory Container 
 * @details The AbstractFactory is doing all the 'magic', this class only holds specialized builders
 */
template< class T >
class Factory
{
protected:
	/**
	 * @brief The vector of specialized builders
	 */
	std::map< std::string, Builder<T>* > mBuilders;
};
