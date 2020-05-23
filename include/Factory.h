#pragma once

#include "Builder.h"
#include <string>
#include <map>

template< class T >
class Factory
{
public:
	std::map< std::string, Builder<T>* > mBuilders;
};
