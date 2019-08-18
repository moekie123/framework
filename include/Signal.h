#pragma once

#include "Configurator.h"

#include <string>
#include <iostream>

class Signal
{
	public:
		Signal( Configurator& _config, std::string _name );
	
    		virtual void write( const int& _value );
    		virtual void read ( int& _value );

	private:
		const std::string mName;
		const std::string mFilename;
};
