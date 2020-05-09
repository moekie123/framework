#include "Generic.h"

#include <string>
#include <iostream>

#include <vector>

const std::map< std::string, int> defaults =
{
    { "const",   0 },
};

Generic::Generic()
{
	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		mProperties[ it->first ] =  it->second;
	}
};

const std::string& Generic::GetName() const
{
    return mName;
}
 
bool Generic::SetName( std::string _name )
{
	mName = _name;
	return true;
}

bool Generic::GetProperty( std::string _property, int& _value ) const
{
	std::vector< std::string > keys;
	for( auto it =  mProperties.begin(); it != mProperties.end(); ++it)
	{
		keys.push_back( it->first );
	}

	for( auto key : keys )
	{
		if ( _property.compare( (mName + "." + key) ) == 0 )
		{
			_value = mProperties.find( key )->second;
			return true;
		}
	}

	return false;
}

bool Generic::SetProperty( std::string _property, const int& _value )
{
	std::vector< std::string > keys;

	if( mProperties.find( "const" )->second == 1 )
		return false;

	for( auto it =  mProperties.begin(); it != mProperties.end(); ++it)
	{
		keys.push_back( it->first );
	}

	for( auto key : keys )
	{
		if ( _property.compare( (mName + "." + key) ) == 0 )
		{
			mProperties.find( key )->second = _value;
			return true;	
		}
	}

	return false;
}

