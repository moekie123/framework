#include "Signal.h"

#include "IConfigurator.h"

#include <string>
#include <iostream>
#include <fstream>

Signal::Signal( const IConfigurator& _config, const std::string& _name ):
	mName( _name )
{

}


void Signal::Write( const int& _value )
{
	std::ofstream file;

 	file.open( mFilename );
  	
	if ( file.is_open() )
  		file << _value;
  	
	file.close();	
}

void Signal::Read( int& _value )
{
	std::ifstream file;

 	file.open( mFilename );

	if ( file.is_open() )
		file >> _value;
	
	file.close();
}
