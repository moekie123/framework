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

Parameter::Parameter( IConfigurator* _config, std::string _name )
{
    	mName = _name;
    	mProperties.insert ( defaults.begin(), defaults.end() );

	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		int value;
		
		std::string pName = mName + "." + it->first;
		
		mProperties[ pName ] =  it->second;
	
	       	if ( _config->GetProperty( pName , value ))
		{
			mProperties[ pName ] =  value;
		}
	}
}
 
void Parameter::Reset()
{
	if ( mProperties.find( mName + ".const" )->second == 0 )
	{
		SetProperty( mName + ".value",  mProperties.find( mName + ".default" )->second );

		// Composite
	    	for( auto* component : mComponents )
		{
			component->Reset();
		}
	}

}

bool Parameter::SetProperty( std::string _property, const int& _value )
{
	bool result = false;

	if ( mProperties.find( mName + ".const" )->second == 0 )
	{
		result = Generic::SetProperty( _property, _value );

		//  TODO: Ff const is set, also the nested (composite) elements needs to be set to const
	}
	else
	{
		// Composite
		for( auto* component : mComponents )
		{
			result = component->SetProperty( _property, _value );
			if( result ) 
				break;
		}
	}
	
	return result;
}

bool Parameter::Update( IParameter *subject )
{
	// Composite
	for( auto* component : mComponents )
	{
		component->Update( subject );
	}

	return true;
}

