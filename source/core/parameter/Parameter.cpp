#include "Parameter.h"

#include "IParameter.h"

#include "Generic.h"
#include "Configurator.h"

#include <map>

Parameter::ParameterBuilder Parameter::builder;

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

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
 
void Parameter::reset()
{
    setProperty( "value",  mProperties.find( "default" )->second );
}


void Parameter::update( IParameter *subject )
{

}
