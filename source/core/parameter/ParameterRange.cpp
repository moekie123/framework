#include "IParameter.h"
#include "Parameter.h"
#include "ParameterRange.h"

#include "Configurator.h"

#include <map>

#include <iostream>

const std::map< std::string, int> defaults =
{
    { "maximum", 0 },
    { "minimum", 0 },
};
 
ParameterRange::ParameterRange()
{}
 
ParameterRange::ParameterRange( Configurator& _config, std::string _name ):
    Parameter( _config, _name )
{
    mProperties.insert ( defaults.begin(), defaults.end() );
}
 
void ParameterRange::setProperty( std::string _property, int _value )
{
    if ( mProperties.find( "const" )->second == 0 )
    {
        if ( !(_property.compare("value")) ||  !(_property.compare("default")) )
        {
            int min = mProperties.find( "minimum" )->second;
            int max = mProperties.find( "maximum" )->second;
            
            if ( (min < _value) && ( _value < max) )
            {
                mProperties.find( _property )->second = _value;
            }
        }
        else if ( !_property.compare( "minimum" ) )
        {
            if ( _value <   mProperties.find( "value" )->second )
                mProperties.find( _property )->second = _value;
        }
        else if ( !_property.compare( "maximum" ) )
        {
            if ( _value >  mProperties.find( "value" )->second )
                mProperties.find( _property )->second = _value;
        }
        else
            mProperties.find( _property )->second = _value;
    }
}
