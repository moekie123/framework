#include "Generic.h"

#include <string>
#include <iostream>

Generic::Generic()
{
	mProperties[ "const" ] = 0;
};

const std::string& Generic::GetName() const
{
    return mName;
}
 
bool Generic::GetProperty( std::string _property, int& _value ) const
{
	if ( mProperties.find( _property ) != mProperties.end() )
	{
   		_value = mProperties.find( _property )->second;
		return true;
	}

	return false;
}

bool Generic::SetProperty( std::string _property, const int& _value )
{
   	if ( mProperties.find( _property ) != mProperties.end() )
	{
		mProperties.find( _property )->second = _value;
		return true;
	}
	return false;
}

