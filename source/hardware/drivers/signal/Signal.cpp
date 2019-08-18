#include "Signal.h"

#include "Configurator.h"

#include <string>
#include <iostream>
#include <fstream>

Signal::Signal( Configurator& _config, std::string _name ):
	mName( _name )
{

}


void Signal::write( const int& _value )
{
	std::ofstream file;

 	file.open( mFilename );
  	
	if ( file.is_open() )
  		file << _value;
  	
	file.close();	
}

void Signal::read( int& _value )
{
	std::ifstream file;

 	file.open( mFilename );

	if ( file.is_open() )
		file >> _value;
	
	file.close();
}
