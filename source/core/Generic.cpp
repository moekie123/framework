#include "Generic.h"

Generic::Generic()
{
	mProperties[ "const" ] = 0;
};

const std::string& Generic::getName() const
{
    return mName;
}
 
const int& Generic::getProperty( std::string _property ) const
{
    return mProperties.find( _property )->second;
}

void Generic::setProperty( std::string _property, int _value )
{
    if ( mProperties.find( "const" )->second == 0 )
        mProperties.find( _property )->second = _value;
}


