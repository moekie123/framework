#include "IParameter.h"
#include "Parameter.h"

#include <map>

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

Parameter::Parameter():
    Parameter( "Unknown" )
{}
 
Parameter::Parameter( std::string _name )
{
    mName = _name;
    mProperties.insert ( defaults.begin(), defaults.end() );
}
 
const int& Parameter::getProperty( std::string _property ) const
{
    return mProperties.find( _property )->second;
}

void Parameter::setProperty( std::string _property, int _value )
{
    if ( mProperties.find( "const" )->second == 0 )
        mProperties.find( _property )->second = _value;
}

Generic* Parameter::build( std::string _name )
{
    return new Parameter( _name );
}

void Parameter::reset()
{
    setProperty( "value",  mProperties.find( "default" )->second );
}

void Parameter::update( IParameter *subject )
{

}
