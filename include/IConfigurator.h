#pragma once

#include <string>
#include <map>

/**
 * TODO This should be implmented
 */
class IConfigurator
{
	public:
		virtual const int& getProperty( std::string ) const;
};
