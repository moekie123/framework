#include "Parameter.h"

#include "IParameter.h"

#include "Generic.h"
#include "IConfigurator.h"

#include <map>

Parameter::ParameterBuilder Parameter::builder;

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

Parameter::Parameter( IConfigurator* _config, std::string _name )
{
    	mName = _name;
    	mProperties.insert ( defaults.begin(), defaults.end() );

	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		int value;
		
		mProperties[ it->first ] =  it->second;

	       	if ( _config->GetProperty( _name + "." + it->first , value ))
		{
			mProperties[ it->first ] =  value;
		}
	}
}
 
void Parameter::Reset()
{
    SetProperty( "value",  mProperties.find( "default" )->second );
}


bool Parameter::SetProperty( std::string _property, const int& _value )
{
	if ( mProperties.find( "const" )->second == 0 )
	{
		return Generic::SetProperty( _property, _value );
	}
	return false;
}

bool Parameter::Update( IParameter *subject )
{
	return false;
}
