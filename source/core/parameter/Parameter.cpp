#include "Parameter.h"

#include "IParameter.h"

#include "Generic.h"
#include "IConfigurator.h"

#include <map>
#include <iostream>

Parameter::ParameterBuilder Parameter::builder;

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

Parameter::Parameter( const IConfigurator& _config, const std::string& _name )
{
	SetName( _name );
    	
	mProperties.insert ( defaults.begin(), defaults.end() );

	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		int value;
		
		mProperties[ it->first ] =  it->second;
	
	       	if ( _config.GetProperty( mName, it->first, value ))
		{
			mProperties[ it->first ] =  value;
		}
	}
}
 
bool Parameter::Reset()
{
	if ( mProperties.find( "const" )->second == 0 )
	{
		SetProperty( mName + ".value",  mProperties.find( "default" )->second );

		// Composite
	    	for( auto* component : mComponents )
		{
			component->Reset();
		}
	}
	return true;
}

bool Parameter::GetProperty( const std::string& _property, int& _value )
{
	bool result = false;

	result = Generic::GetProperty( _property, _value );

	return result;
}

bool Parameter::SetProperty( const std::string& _property, const int& _value )
{
	bool result = false;

	result = Generic::SetProperty( _property, _value );
	
	return result;
}

bool Parameter::Update( const Subject& subject )
{
	for( auto* component : mComponents )
	{
// TODO
//		component->Update( subject );
	}
	return true;
}

