#include "Configurator.h"
#include "IParameter.h"
#include "Parameter.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include <map>

Parameter::ParameterBuilder Parameter::builder;

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

Parameter::Parameter()
{}
 
Parameter::Parameter( Configurator& _config, std::string _name )
{
    	mName = _name;
    	mProperties.insert ( defaults.begin(), defaults.end() );

	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		int value;
		 _config.getProperty( _name , it->first , value );

		mProperties[ it->first ] =  value;
	}
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

void Parameter::reset()
{
    setProperty( "value",  mProperties.find( "default" )->second );
}

void Parameter::update( IParameter *subject )
{

}
