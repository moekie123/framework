#include "Generic.h"

Generic::Generic()
{
	mProperties[ "const" ] = 0;
};

const std::string& Generic::getName() const
{
    return mName;
}
 
bool Generic::getProperty( std::string _property, int& _value ) const
{
   	if ( mProperties.find( _property ) == mProperties.end() )
	{
   		_value = mProperties.find( _property )->second;
		return true;
	}

	return false;
}

bool Generic::setProperty( std::string _property, const int& _value )
{
   	if ( mProperties.find( _property ) == mProperties.end() )
	{
		if ( mProperties.find( "const" )->second == 0 )
		{
			mProperties.find( _property )->second = _value;
			return true;
		}
	}
	return false;
}
