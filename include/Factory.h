#pragma once

#include "Builder.h"
#include <string>
#include <map>

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
