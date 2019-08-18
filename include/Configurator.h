#pragma once

#include <string>
#include <map>

class Configurator
{
	public:
		Configurator( std::string = "default.config" );

		virtual bool getProperty( std::string, std::string, int& ) const;
		virtual bool setProperty( std::string, std::string, const int& );

		virtual bool getSignal( std::string, std::string, std::string& ) const;

	private:
		std::map < std::string, int > mProperties;
};
