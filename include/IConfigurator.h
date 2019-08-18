#pragma once

#include <string>
#include <map>

class IConfigurator
{
	public:
		virtual const int& getProperty( std::string ) const;
};
