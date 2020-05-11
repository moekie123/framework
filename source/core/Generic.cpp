#include "Generic.h"

#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

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
 
bool Generic::SetName( const std::string& _name )
{
	mName = _name;
	return true;
}

bool Generic::GetProperty( const std::string& _property, int& _value ) const
{
	auto property = std::find_if( mProperties.begin(), mProperties.end(), [ this, _property ]( auto const& property )
	{
		if( _property.compare( mName + "." + property.first ) == 0 )
		{
			return true;
		}

		return false;
	});

	if( property != mProperties.end() )
	{
		_value = property->second;
		return true;
	}
		
	return false;
}

bool Generic::SetProperty( const std::string& _property, const int& _value )
{
	if( mProperties.find( "const" )->second == 1 )
		return false;

	auto property = std::find_if( mProperties.begin(), mProperties.end(), [ this, _property ]( auto const& property )
	{
		if( _property.compare( mName + "." + property.first ) == 0 )
		{
			return true;
		}

		return false;
	});

	if( property != mProperties.end() )
	{
		property->second = _value;
		return true;
	}

	return false;
}

